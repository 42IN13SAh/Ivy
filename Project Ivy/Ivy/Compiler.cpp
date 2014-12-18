#include "Compiler.h"
#include "InternalFunctionFactory.h"
#include "SymbolTableItemsToBeDeleted.h"

Compiler::Compiler(std::list<Token*> tokenList) {
	hasFatalError = false;
	this->tokenList = tokenList;
	this->firstAction = new DoNothingAction();
	this->lastAction = firstAction;
	this->globalSymbolTable = new SymbolTable();
	resetTokenIter();
}

Compiler::~Compiler() 
{
	Action *currentActionPtr = this->getFirstAction();
	Action *nextActionPtr = currentActionPtr->getNextAction();
	Action *onFalseActionPtr;
	while (nextActionPtr != nullptr){
		nextActionPtr = currentActionPtr->getNextAction();
		onFalseActionPtr = currentActionPtr->getFalseAction();
		delete currentActionPtr;
		if (onFalseActionPtr != nullptr){
			delete onFalseActionPtr;
		}
		currentActionPtr = nextActionPtr;
	}
	SymbolTableItemsToBeDeleted *items = currentSymbolTable->getItemsToDelete();
	for each (Symbol *symbol in items->getSymbols())
	{
		delete symbol;
	}
	for each (FunctionSymbol *functionSymbol in items->getFunctionSymbols())
	{
		delete functionSymbol;
	}
	delete items;
	if (currentSymbolTable != globalSymbolTable){
		delete globalSymbolTable;
	}
	delete currentSymbolTable;
}

void Compiler::compile() 
{
	currentSymbolTable = globalSymbolTable;
	addInternalFunctions();
	while (tokenIter != tokenList.end() && !hasFatalError) {
		if (getCurrentToken()->getTokenType() == TokenType::Function){
			addFunctionSignature();
			// check fatal
			if (hasFatalError) { return; }
		}
		else if (getCurrentToken()->getLevel() == 0 && (getCurrentToken()->getTokenType() == TokenType::Var || getCurrentToken()->getTokenType() == TokenType::Name)){
			compileStatement();
			// check fatal
			if (hasFatalError) { return; }
		}
		else{
			tokenIter++;
		}
	}
	resetTokenIter();
	if (hasFatalError)
		return;
	while (tokenIter != tokenList.end() && !hasFatalError) {
		if (getCurrentToken()->getLevel() == 0 && getCurrentToken()->getTokenType() == TokenType::Function){
			compileFunction();
			// check fatal
			if (hasFatalError) { return; }
		}
		else{
			tokenIter++;
		}
	}
}

void Compiler::compileFunction() 
{
	// TODO: delete all new classes
	Action* startFunction = new Action(); 
	FunctionCompilerToken* fct = new FunctionCompilerToken(getNextToken()->getDescription());
	Token* start = getNextToken();
	if (start == nullptr) return;
	while (getCurrentToken()->getPartner() != start) {
		if (getCurrentToken()->getTokenType() == TokenType::Name) {
			fct->addArgumentName(getCurrentToken()->getDescription());
		}
		if (getNextToken() == nullptr) return;
	}
	if (getNextToken() == nullptr) return;
	startFunction->setCompilerToken(fct);
	startFunction->setNextAction(new DoNothingAction());
	lastAction = startFunction->getNextAction();
	FunctionSymbol* functionSymbol = currentSymbolTable->getFunctionSymbol(fct->getName(), fct->getArgumentNames().size());
	functionSymbol->setStartAction(startFunction);
	currentSymbolTable = functionSymbol->getSymbolTable();
	compileCodeBlock();
	// check fatal
	if (hasFatalError) { return; }
	currentSymbolTable = globalSymbolTable;
	functionSymbol->setEndAction(lastAction);
}

void Compiler::addFunctionSignature()
{
	if ((dTok = getNextToken()) == nullptr) return;
	std::string name = dTok->getDescription();
	if ((dTok = getNextToken()) == nullptr) return;
	Token* start = dTok;
	int params = 0;
	while (getCurrentToken()->getPartner() != start) {
		if (getCurrentToken()->getTokenType() == TokenType::Name) {
			params++;
		}
		if (getNextToken() == nullptr) return;
	}
	if (getNextToken() == nullptr) return;
	currentSymbolTable->addFunctionSymbol(new FunctionSymbol(name, params, nullptr, nullptr, false));
}

void Compiler::compileCodeBlock()
{
	Token* start = getCurrentToken();
	while (getCurrentToken()->getPartner() != start) {
		Action* last = lastAction;
		switch (getCurrentToken()->getTokenType()) {
			case TokenType::WhileStatement:
				compileWhile();
				// check fatal
				if (hasFatalError) { return; }
				break;
			case TokenType::IfStatement:
				compileIf();
				// check fatal
				if (hasFatalError) { return; }
				break;
			case TokenType::Function:
				throw new std::exception;
				break;
			default:
				compileStatement();
				// check fatal
				if (hasFatalError) { return; }
				break;
		}
		if (last == lastAction){
			if (getNextToken() == nullptr) return;
		}
	}
}

void Compiler::compileStatement() 
{
	Action* statement = new Action();
	switch (getCurrentToken()->getTokenType()) {
		case TokenType::Var:
			statement = compileStatementVar(statement);
			break;
		case TokenType::Name:
			statement = compileStatementName(statement);
			break;
		case TokenType::Return:
			if (getNextToken() == nullptr) return;
			statement->setCompilerToken(new ReturnCompilerToken(compileReturnValue()));
			// check fatal, delete statement
			if (hasFatalError) { delete statement; return; }
			break;
		case TokenType::IncreaseOperator: case TokenType::DecreaseOperator:
			{
				TokenType::TokenType op = getCurrentToken()->getTokenType();
				if ((dTok = getNextToken()) == nullptr) return;
				VarCompilerToken* v = new VarCompilerToken(dTok->getDescription());
				v->setFrontOperator(op);
				statement->setCompilerToken(v);
				if (getNextToken() == nullptr) { delete statement; return; }
				//- detele statement
				break;
			}		
	}
	if (statement != nullptr && statement->getCompilerToken() != nullptr) {
		lastAction->setNextAction(statement);
		statement->setNextAction(new DoNothingAction());
		lastAction = statement->getNextAction();
	}
}

void Compiler::compileWhile() 
{
	// TODO: delete all new classes
	Action* condition = new Action();
	Action* begin = condition;
	if (getNextToken() == nullptr) return;
	condition->setCompilerToken(compileCondition());
	// check fatal
	if (hasFatalError) return;
	lastAction->setNextAction(condition);
	DoNothingAction* onTrue = new DoNothingAction();
	condition->setNextAction(onTrue);
	lastAction = onTrue;
	compileCodeBlock();
	// check fatal
	if (hasFatalError) return;
	lastAction->setNextAction(begin);
	DoNothingAction* onFalse = new DoNothingAction();
	condition->setFalseAction(onFalse);
	lastAction = onFalse;
}

void Compiler::compileIf()
{
	// TODO: delete all new classes
	Token* start = getCurrentToken();
	if (start == nullptr) return;
	Action* ifAction = new Action();
	Action* end = new DoNothingAction();
	if (getNextToken() == nullptr) return;
	ifAction->setCompilerToken(compileCondition());
	// check fatal
	if (hasFatalError) return;
	ifAction->setNextAction(new DoNothingAction());
	lastAction->setNextAction(ifAction);
	lastAction = ifAction->getNextAction();
	compileCodeBlock();
	// check fatal
	if (hasFatalError) return;
	lastAction->setNextAction(end);
	if (start->getPartner() != nullptr && start->getPartner()->getTokenType() == TokenType::ElseStatement){
		if (getNextToken() == nullptr) return;
		ifAction->setFalseAction(compileElse());
		// check fatal
		if (hasFatalError) return;
	}
	else{
		ifAction->setFalseAction(end);
	}
	lastAction->setNextAction(end);
	lastAction = end;
	if (getNextToken() == nullptr) return;
}

Action* Compiler::compileElse()
{
	DoNothingAction* elseAction = new DoNothingAction();
	lastAction = elseAction;
	if (getNextToken() == nullptr) return nullptr;
	compileCodeBlock();
	// check fatal
	if (hasFatalError) return nullptr;
	return elseAction;
}

ReturnValueCompilerToken* Compiler::compileReturnValue() 
{
	//int openParenthisCounter = 0;
	std::vector<TokenType::TokenType> endTypes = { TokenType::LineEnd, TokenType::ParameterOperator, TokenType::OpenBracket };
	Token* cToken = getCurrentToken();
	ReturnValueCompilerToken* rt = new ReturnValueCompilerToken();
	while (std::find(endTypes.begin(), endTypes.end(), cToken->getTokenType()) == endTypes.end() && !(getCurrentToken()->getTokenType() == TokenType::ClosingParenthesis && !rt->hasOpenParenthisOnStack())) {
		if (cToken->getTokenType() == TokenType::Name){
			compileReturnValueName(rt);
			// check fatal
			if (hasFatalError) return nullptr;
		}
		else if (cToken->getTokenType() == TokenType::IncreaseOperator || cToken->getTokenType() == TokenType::DecreaseOperator){
			compileReturnValueIncreaseDecrease(rt);
			// check fatal
			if (hasFatalError) return nullptr;
		}
		else if (cToken->getParentType() == ParentType::MathOperator || cToken->getParentType() == ParentType::ConditionOperator || cToken->getParentType() == ParentType::SubConditionOperator
			|| cToken->getTokenType() == TokenType::OpenParenthesis || cToken->getTokenType() == TokenType::ClosingParenthesis){
			compileReturnValueMath(rt);
			// check fatal
			if (hasFatalError) return nullptr;
		}
		else{
			switch (cToken->getTokenType()){
			case TokenType::Number:
				rt->addValueToVector(stod(cToken->getDescription()));
				break;
			case TokenType::BooleanTrue: case TokenType::BooleanFalse:
				rt->addValueToVector(cToken->getDescription().compare("true") == 0);
				break;
			default:
				rt->addValueToVector(cToken->getDescription());
			}
		}
		cToken = getNextToken();
		if (cToken == nullptr) return nullptr;
	}
	rt->completeRPNVector();
	return rt;
}

ConditionCompilerToken* Compiler::compileCondition() 
{
	Token* start = nullptr;
	if (getCurrentToken()->getTokenType() == TokenType::OpenParenthesis){
		start = getCurrentToken();
	}
	if (getNextToken() == nullptr) return nullptr;
	ConditionCompilerToken* cct = new ConditionCompilerToken(compileReturnValue());
	// check fatal
	if (hasFatalError) return nullptr;
	if (getNextToken() == nullptr) return nullptr;
	return cct;
}

FunctionCompilerToken* Compiler::compileFunctionCall() 
{
	FunctionCompilerToken* fct = new FunctionCompilerToken(getCurrentToken()->getDescription());
	Token* start = getNextToken();
	if (start == nullptr) return nullptr;
	while (getCurrentToken()->getPartner() != start) {
		if ((dTok = getNextToken()) == nullptr) return nullptr;
		if (dTok->getPartner() != start) {
			fct->addArgument(compileReturnValue());
			// check fatal
			if (hasFatalError) return nullptr;
		}
	}
	return fct;
}

Action* Compiler::compileStatementVar(Action* statement) 
{
	if ((dTok = getNextToken())== nullptr) return nullptr;
	std::string name = dTok->getDescription();
	if ((dTok = getNextToken()) == nullptr) return nullptr;
	if (dTok->getTokenType() == TokenType::AssignmentOperator) {
		if (getNextToken() == nullptr) return nullptr;
		statement->setCompilerToken(new AssignCompilerToken(name, compileReturnValue(), TokenType::AssignmentOperator));
		// check fatal
		if (hasFatalError) return nullptr;
	}
	else{
		statement = nullptr;
	}
	if (currentSymbolTable->hasSymbol(name)){
		throw new std::exception; // TODO: better exception handling
	}
	else{
		currentSymbolTable->addSymbolToTable(name);
	}
	return statement;
}

Action* Compiler::compileStatementName(Action* statement) 
{
	std::string name = getCurrentToken()->getDescription();
	if ((dTok = peekNextToken()) == nullptr) return nullptr;
	if (dTok->getTokenType() == TokenType::OpenParenthesis){
		statement->setCompilerToken(compileFunctionCall());
		// check fatal
		if (hasFatalError) return nullptr;
	}
	else if (currentSymbolTable->hasSymbol(name) || globalSymbolTable->hasSymbol(name)) { // TODO: symboltable exception handling
		if ((dTok = getNextToken()) == nullptr) return nullptr;
		TokenType::TokenType op = dTok->getTokenType();
		if (getNextToken() == nullptr) return nullptr;
		switch (op) {
			case TokenType::AssignmentOperator: case TokenType::AddThenAssignOperator: case TokenType::MinusThenAssignOperator: case TokenType::DivideThenAssignOperator: case TokenType::MultiplyThenAssignOperator:
				statement->setCompilerToken(new AssignCompilerToken(name, compileReturnValue(), op));
				// check fatal
				if (hasFatalError) return nullptr;
				break;
			case TokenType::IncreaseOperator: case TokenType::DecreaseOperator:{
				VarCompilerToken* v = new VarCompilerToken(name);
				v->setBackOperator(op);
				statement->setCompilerToken(v);
				break;
			}
		}
	}
	return statement;
}

void Compiler::compileReturnValueName(ReturnValueCompilerToken* rt)
{
	if ((dTok = peekNextToken()) == nullptr) return;
	if (dTok->getTokenType() == TokenType::OpenParenthesis){
		rt->addValueToVector(compileFunctionCall());
		// check fatal
		if (hasFatalError) return;
	}
	else {
		VarCompilerToken* v = new VarCompilerToken(getCurrentToken()->getDescription());
		if (dTok->getTokenType() == TokenType::IncreaseOperator || dTok->getTokenType() == TokenType::DecreaseOperator){
			if (getNextToken() == nullptr) return;
			v->setBackOperator(dTok->getTokenType());
		}
		rt->addValueToVector(v);
	}
}

void Compiler::compileReturnValueIncreaseDecrease(ReturnValueCompilerToken* rt) 
{
	if ((dTok = peekNextToken()) == nullptr) return;
	VarCompilerToken* v = new VarCompilerToken(dTok->getDescription());
	v->setFrontOperator(getCurrentToken()->getTokenType());
	rt->addValueToVector(v);
	getNextToken();
}

void Compiler::compileReturnValueMath(ReturnValueCompilerToken* rt)
{
	if (getCurrentToken()->getTokenType() == TokenType::OpenParenthesis){
		rt->pushOperatorToStack(getCurrentToken()->getTokenType());
	}
	else if (getCurrentToken()->getParentType() == ParentType::MathOperator){
		if (!rt->isEmpty()){
			TokenType::TokenType tmp = rt->peekOperatorStack();
			if (tmp == TokenType::DivideOperator || tmp == TokenType::ModuloOperator || tmp == TokenType::MultiplyOperator){
				rt->addValueToVector(tmp);
				rt->popOperatorStack();
			}
			else if ((getCurrentToken()->getTokenType() == TokenType::AddOperator || getCurrentToken()->getTokenType() == TokenType::MinusOperator) &&
				(tmp == TokenType::AddOperator || tmp == TokenType::MinusOperator)){
				rt->addValueToVector(tmp);
				rt->popOperatorStack();
			}
		}
		rt->pushOperatorToStack(getCurrentToken()->getTokenType());
	}
	else if (getCurrentToken()->getTokenType() == TokenType::ClosingParenthesis){
		while (rt->peekOperatorStack() != TokenType::OpenParenthesis){
			rt->addValueToVector(rt->peekOperatorStack());
			rt->popOperatorStack();
		}
		rt->popOperatorStack();
	}
	else if (getCurrentToken()->getParentType() == ParentType::SubConditionOperator){
		if (!rt->isEmpty()){
			if (rt->peekOperatorStack() != TokenType::OrStatement && rt->peekOperatorStack() != TokenType::AndStatement){
				rt->addValueToVector(rt->peekOperatorStack());
				rt->popOperatorStack();
			}
		}
		rt->pushOperatorToStack(getCurrentToken()->getTokenType());
	}
	else if (getCurrentToken()->getParentType() == ParentType::ConditionOperator){
		if (!rt->isEmpty()){
			rt->addValueToVector(rt->peekOperatorStack());
			rt->popOperatorStack();
		}
		rt->pushOperatorToStack(getCurrentToken()->getTokenType());
	}
}

void Compiler::addInternalFunctions() 
{
	for each(auto iter in InternalFunctionFactory::Instance()->GetArgNrMap()) {
		currentSymbolTable->addFunctionSymbol(new FunctionSymbol(iter.first, iter.second, nullptr, nullptr, true));
	}
}

Token* Compiler::getCurrentToken() 
{
	return *tokenIter; 
}
Token* Compiler::getNextToken()
{ 
	Token* tmp = (++tokenIter != tokenList.end()) ? *tokenIter : nullptr;
	if (tmp == nullptr) {
		Token* last = *--tokenIter;
		errorList.push_back(UnexpectedEndOfFileException(last->getLineNumber(), last->getLinePosition(), last->getSyntaxID(), last->getDescription()));
		++tokenIter;
		hasFatalError = true;
	}
	return tmp;
}

Token* Compiler::peekNextToken() 
{
	Token* temp = getNextToken();
	tokenIter--;
	return temp;
}

void Compiler::resetTokenIter() 
{ 
	tokenIter = tokenList.begin();
}

Action* Compiler::getFirstAction() 
{ 
	return firstAction; 
}

SymbolTable* Compiler::getSymbolTable() 
{ 
	return globalSymbolTable; 
}

const std::vector<BaseException>& Compiler::getErrorList() {
	return errorList;
}