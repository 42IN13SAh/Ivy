#include "Compiler.h"
#include "InternalFunctionFactory.h"
#include "SymbolTableItemsToBeDeleted.h"

Compiler::Compiler(std::list<Token*> tokenList) {
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
	while (tokenIter != tokenList.end()) {
		if (getCurrentToken()->getTokenType() == TokenType::Function){
			addFunctionSignature();
		}
		else if (getCurrentToken()->getLevel() == 0 && (getCurrentToken()->getTokenType() == TokenType::Var || getCurrentToken()->getTokenType() == TokenType::Name)){
			compileStatement();
		}
		else{
			tokenIter++;
		}
	}
	resetTokenIter();
	while (tokenIter != tokenList.end()) {
		if (getCurrentToken()->getLevel() == 0 && getCurrentToken()->getTokenType() == TokenType::Function){
			compileFunction();
		}
		else{
			tokenIter++;
		}
	}
}

void Compiler::compileFunction() 
{

	Action* startFunction = new Action(); 
	FunctionCompilerToken* fct = new FunctionCompilerToken(getNextToken()->getDescription());
	Token* start = getNextToken();
	while (getCurrentToken()->getPartner() != start) {
		if (getCurrentToken()->getTokenType() == TokenType::Name) {
			fct->addArgumentName(getCurrentToken()->getDescription());
		}
		getNextToken();
	}
	getNextToken();
	startFunction->setCompilerToken(fct);
	startFunction->setNextAction(new DoNothingAction());
	lastAction = startFunction->getNextAction();
	FunctionSymbol* functionSymbol = currentSymbolTable->getFunctionSymbol(fct->getName(), fct->getArgumentNames().size());
	functionSymbol->setStartAction(startFunction);
	currentSymbolTable = functionSymbol->getSymbolTable();
	compileCodeBlock();
	currentSymbolTable = globalSymbolTable;
	functionSymbol->setEndAction(lastAction);
}

void Compiler::addFunctionSignature()
{
	std::string name = getNextToken()->getDescription();
	Token* start = getNextToken();
	int params = 0;
	while (getCurrentToken()->getPartner() != start) {
		if (getCurrentToken()->getTokenType() == TokenType::Name) {
			params++;
		}
		getNextToken();
	}
	getNextToken();
	currentSymbolTable->addFunctionSymbol(new FunctionSymbol(name, params, nullptr, nullptr, false));
}

void Compiler::compileCodeBlock()
{
	while (getCurrentToken()->getTokenType() != TokenType::ClosingBracket) {
		Action* last = lastAction;
		switch (getCurrentToken()->getTokenType()) {
			case TokenType::WhileStatement:
				compileWhile();
				break;
			case TokenType::IfStatement:
				compileIf();
				break;
			case TokenType::Function:
				throw new std::exception;
				break;
			default:
				compileStatement();
				break;
		}
		if (last == lastAction){
			getNextToken();
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
			getNextToken();
			statement->setCompilerToken(new ReturnCompilerToken(compileReturnValue()));
			break;
		case TokenType::IncreaseOperator: case TokenType::DecreaseOperator:
			{
				TokenType op = getCurrentToken()->getTokenType();
				VarCompilerToken* v = new VarCompilerToken(getNextToken()->getDescription());
				v->setFrontOperator(op);
				statement->setCompilerToken(v);
				getNextToken();
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
	Action* condition = new Action();
	Action* begin = condition;
	getNextToken();
	condition->setCompilerToken(compileCondition());
	lastAction->setNextAction(condition);
	DoNothingAction* onTrue = new DoNothingAction();
	condition->setNextAction(onTrue);
	lastAction = onTrue;
	compileCodeBlock();
	lastAction->setNextAction(begin);
	DoNothingAction* onFalse = new DoNothingAction();
	condition->setFalseAction(onFalse);
	lastAction = onFalse;
}

void Compiler::compileIf()
{
	Token* start = getCurrentToken();
	Action* ifAction = new Action();
	Action* end = new DoNothingAction();
	getNextToken();
	ifAction->setCompilerToken(compileCondition());
	ifAction->setNextAction(new DoNothingAction());
	lastAction->setNextAction(ifAction);
	lastAction = ifAction->getNextAction();
	compileCodeBlock();
	lastAction->setNextAction(end);
	if (start->getPartner() != nullptr && start->getPartner()->getTokenType() == TokenType::ElseStatement){
		ifAction->setFalseAction(compileElse());
	}
	else{
		ifAction->setFalseAction(end);
	}
	lastAction->setNextAction(end);
	lastAction = end;
	getNextToken();
}

Action* Compiler::compileElse()
{
	DoNothingAction* elseAction = new DoNothingAction();
	lastAction = elseAction;
	getNextToken();
	compileCodeBlock();
	return elseAction;
}

ReturnValueCompilerToken* Compiler::compileReturnValue() 
{
	int openParenthisCounter = 0;
	std::vector<TokenType> endTypes = { TokenType::LineEnd, TokenType::ParameterOperator, TokenType::OpenBracket };
	Token* cToken = getCurrentToken();
	ReturnValueCompilerToken* rt = new ReturnValueCompilerToken();
	while (std::find(endTypes.begin(), endTypes.end(), cToken->getTokenType()) == endTypes.end() && !(getCurrentToken()->getTokenType() == TokenType::ClosingParenthesis && !rt->hasOpenParenthisOnStack())) {
		if (cToken->getTokenType() == TokenType::Name){
			compileReturnValueName(rt);
		}
		else if (cToken->getTokenType() == TokenType::IncreaseOperator || cToken->getTokenType() == TokenType::DecreaseOperator){
			compileReturnValueIncreaseDecrease(rt);
		}
		else if (cToken->getParentType() == ParentType::MathOperator || cToken->getParentType() == ParentType::ConditionOperator || cToken->getParentType() == ParentType::SubConditionOperator
			|| cToken->getTokenType() == TokenType::OpenParenthesis || cToken->getTokenType() == TokenType::ClosingParenthesis){
			compileReturnValueMath(rt);
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
	getNextToken();
	ConditionCompilerToken* cct = new ConditionCompilerToken(compileReturnValue());
	getNextToken();
	return cct;
}

FunctionCompilerToken* Compiler::compileFunctionCall() 
{
	FunctionCompilerToken* fct = new FunctionCompilerToken(getCurrentToken()->getDescription());
	Token* start = getNextToken();
	while (getCurrentToken()->getPartner() != start) {
		if (getNextToken()->getPartner() != start)
			fct->addArgument(compileReturnValue());
	}
	return fct;
}

Action* Compiler::compileStatementVar(Action* statement) 
{
	std::string name = getNextToken()->getDescription();
	if (getNextToken()->getTokenType() == TokenType::AssignmentOperator) {
		getNextToken();
		statement->setCompilerToken(new AssignCompilerToken(name, compileReturnValue(), TokenType::AssignmentOperator));
	}
	else{
		statement = nullptr;
	}
	if (currentSymbolTable->hasSymbol(name)){
		throw new std::exception;
	}
	else{
		currentSymbolTable->addSymbolToTable(name);
	}
	return statement;
}

Action* Compiler::compileStatementName(Action* statement) 
{
	std::string name = getCurrentToken()->getDescription();
	if (peekNextToken()->getTokenType() == TokenType::OpenParenthesis){
		statement->setCompilerToken(compileFunctionCall());
	}
	else if (currentSymbolTable->hasSymbol(name) || globalSymbolTable->hasSymbol(name)) {
		TokenType op = getNextToken()->getTokenType();
		getNextToken();
		switch (op) {
			case TokenType::AssignmentOperator: case TokenType::AddThenAssignOperator: case TokenType::MinusThenAssignOperator: case TokenType::DivideThenAssignOperator: case TokenType::MultiplyThenAssignOperator:
				statement->setCompilerToken(new AssignCompilerToken(name, compileReturnValue(), op));
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
	if (peekNextToken()->getTokenType() == TokenType::OpenParenthesis){
		rt->addValueToVector(compileFunctionCall());
	}
	else {
		VarCompilerToken* v = new VarCompilerToken(getCurrentToken()->getDescription());
		if (peekNextToken()->getTokenType() == TokenType::IncreaseOperator || peekNextToken()->getTokenType() == TokenType::DecreaseOperator){
			v->setBackOperator(getNextToken()->getTokenType());
		}
		rt->addValueToVector(v);
	}
}

void Compiler::compileReturnValueIncreaseDecrease(ReturnValueCompilerToken* rt) 
{
	VarCompilerToken* v = new VarCompilerToken(peekNextToken()->getDescription());
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
			TokenType tmp = rt->peekOperatorStack();
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
	return (tokenIter != tokenList.end()) ? *++tokenIter : nullptr; 
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