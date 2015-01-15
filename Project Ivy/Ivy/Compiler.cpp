#include <boost/shared_ptr.hpp>
#include "Compiler.h"
#include "InternalFunctionFactory.h"

Compiler::Compiler(std::list<Token*> tokenList) {
	hasFatalError = false;
	this->tokenList = tokenList;
	this->firstAction = createDoNothing();
	this->lastAction = firstAction;
	this->globalSymbolTable = new SymbolTable();
	resetTokenIter();
}

Compiler::~Compiler() 
{
	delete globalSymbolTable;
	for (int i = 0; i < actions.size(); i++){
		delete actions[i];
	}
}

void Compiler::compile() 
{
   	currentSymbolTable = globalSymbolTable;
  	addInternalFunctions();
	while (tokenIter != tokenList.end() && !hasFatalError) {
		if (getCurrentToken()->getTokenType() == TokenType::Function){
			addFunctionSignature();
			if (hasFatalError) return;
		}
		else if (getCurrentToken()->getLevel() == 0 && (getCurrentToken()->getTokenType() == TokenType::Var || getCurrentToken()->getTokenType() == TokenType::Name)){
			compileStatement();
			if (hasFatalError) return;
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
			if (hasFatalError) return;
		}
		else{
			tokenIter++;
		}
	}
}

void Compiler::compileFunction() 
{
	Action* startFunction = createAction(); 
	boost::shared_ptr<FunctionCompilerToken> fct = boost::shared_ptr<FunctionCompilerToken>(new FunctionCompilerToken(getNextToken()->getDescription()));
	Token* start = getNextToken();
	if (start == nullptr) { fct.reset(); return; }
	while (getCurrentToken()->getPartner() != start) {
		if (getCurrentToken()->getTokenType() == TokenType::Name) {
			fct->addArgumentName(getCurrentToken()->getDescription());
		}
		if (getNextToken() == nullptr) { fct.reset(); return; }
	}
	if (getNextToken() == nullptr) { fct.reset(); return; }
	startFunction->setCompilerToken(fct);
	startFunction->setNextAction(createDoNothing());
	lastAction = startFunction->getNextAction();
	FunctionSymbol* functionSymbol = currentSymbolTable->getFunctionSymbol(fct->getName(), fct->getArgumentNames().size());
	functionSymbol->setStartAction(startFunction);
	currentSymbolTable = functionSymbol->getSymbolTable();
	compileCodeBlock();
	if (hasFatalError) { return; }
	currentSymbolTable = globalSymbolTable;
	functionSymbol->setEndAction(lastAction);
}

void Compiler::addFunctionSignature()
{
	Token* fTok = getNextToken();
	if (fTok == nullptr) return;
	std::string name = fTok->getDescription();
	if ((dTok = getNextToken()) == nullptr) return;
	Token* start = dTok;
	int params = 0;
	FunctionSymbol* fs = new FunctionSymbol(name, params, nullptr, nullptr, false);
	while (getCurrentToken()->getPartner() != start) {
		if (getCurrentToken()->getTokenType() == TokenType::Name) {
			params++;
			fs->getSymbolTable()->addSymbolToTable(getCurrentToken()->getDescription());
		}
		if (getNextToken() == nullptr) { delete fs; return; }
	}
	if (getNextToken() == nullptr) { delete fs; return; }
	fs->setArgumentNr(params);
	if (!currentSymbolTable->addFunctionSymbol(fs))
		errorList.push_back(SymbolAlreadyExistsException(fTok->getLineNumber(), fTok->getLinePosition(), name, "Function"));
}

void Compiler::compileCodeBlock()
{
	Token* start = getCurrentToken();
	while (getCurrentToken()->getPartner() != start) {
		Action* last = lastAction;
		switch (getCurrentToken()->getTokenType()) {
			case TokenType::WhileStatement:
				compileWhile();
				if (hasFatalError) return;
				break;
			case TokenType::IfStatement:
				compileIf();
				if (hasFatalError) return;
				break;
			case TokenType::Function:
				errorList.push_back(BaseException(getCurrentToken()->getLineNumber(), getCurrentToken()->getLinePosition(), "Bad syntax exception, new Function not allowed here"));
				break;
			default:
				compileStatement();
				if (hasFatalError) return;
				break;
		}
		if (last == lastAction){
			if (getNextToken() == nullptr) return;
		}
	}
}

void Compiler::compileStatement() 
{
	Action* statement = createAction();
	switch (getCurrentToken()->getTokenType()) {
		case TokenType::Var:
			statement = compileStatementVar(statement);
			break;
		case TokenType::Name:
			statement = compileStatementName(statement);
			break;
		case TokenType::Return:
			if (getNextToken() == nullptr) return;
			statement->setCompilerToken(boost::shared_ptr<ReturnCompilerToken>(new ReturnCompilerToken(compileReturnValue())));
			if (hasFatalError) return;
			break;
		case TokenType::IncreaseOperator: case TokenType::DecreaseOperator:
			{
				TokenType::TokenType op = getCurrentToken()->getTokenType();
				if ((dTok = getNextToken()) == nullptr) return;
				boost::shared_ptr<VarCompilerToken> v = boost::shared_ptr<VarCompilerToken>(new VarCompilerToken(dTok->getDescription()));
				v->setFrontOperator(op);
				statement->setCompilerToken(v);
				if (getNextToken() == nullptr) return;
				break;
			}		
	}
	if (statement != nullptr && statement->getCompilerToken() != nullptr) {
		lastAction->setNextAction(statement);
		statement->setNextAction(createDoNothing());
		lastAction = statement->getNextAction();
	}
}

void Compiler::compileWhile() 
{
	Action* condition = createAction();
	Action* begin = condition;
	if (getNextToken() == nullptr) return;
	condition->setCompilerToken(compileCondition());
	if (hasFatalError) return;
	lastAction->setNextAction(condition);
	DoNothingAction* onTrue = createDoNothing();
	condition->setNextAction(onTrue);
	lastAction = onTrue;
	compileCodeBlock();
	if (hasFatalError) return;
	lastAction->setNextAction(begin);
	DoNothingAction* onFalse = createDoNothing();
	condition->setFalseAction(onFalse);
	lastAction = onFalse;
}

void Compiler::compileIf()
{
	Token* start = getCurrentToken();
	if (start == nullptr) return;
	Action* ifAction = createAction();
	Action* end = createDoNothing();
	if (getNextToken() == nullptr) return;
	ifAction->setCompilerToken(compileCondition());
	if (hasFatalError) return;
	ifAction->setNextAction(createDoNothing());
	lastAction->setNextAction(ifAction);
	lastAction = ifAction->getNextAction();
	compileCodeBlock();
	if (hasFatalError) return;
	lastAction->setNextAction(end);
	if (start->getPartner() != nullptr && start->getPartner()->getTokenType() == TokenType::ElseStatement){
		if (getNextToken() == nullptr) return;
		ifAction->setFalseAction(compileElse());
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
	DoNothingAction* elseAction = createDoNothing();
	lastAction = elseAction;
	if (getNextToken() == nullptr) return nullptr;
	compileCodeBlock();
	if (hasFatalError) return nullptr;
	return elseAction;
}

boost::shared_ptr<ReturnValueCompilerToken> Compiler::compileReturnValue() 
{
	std::vector<TokenType::TokenType> endTypes = { TokenType::LineEnd, TokenType::ParameterOperator, TokenType::OpenBracket };
	Token* cToken = getCurrentToken();
	boost::shared_ptr<ReturnValueCompilerToken> rt = boost::shared_ptr<ReturnValueCompilerToken>(new ReturnValueCompilerToken());
	while (std::find(endTypes.begin(), endTypes.end(), cToken->getTokenType()) == endTypes.end() && !(getCurrentToken()->getTokenType() == TokenType::ClosingParenthesis && !rt->hasOpenParenthisOnStack())) {
		if (cToken->getTokenType() == TokenType::Name){
			compileReturnValueName(rt);
			if (hasFatalError) {  rt.reset(); return nullptr; }
		}
		else if (cToken->getTokenType() == TokenType::IncreaseOperator || cToken->getTokenType() == TokenType::DecreaseOperator){
			compileReturnValueIncreaseDecrease(rt);
			if (hasFatalError) {  rt.reset(); return nullptr; }
		}
		else if (cToken->getParentType() == ParentType::MathOperator || cToken->getParentType() == ParentType::ConditionOperator || cToken->getParentType() == ParentType::SubConditionOperator
			|| cToken->getTokenType() == TokenType::OpenParenthesis || cToken->getTokenType() == TokenType::ClosingParenthesis){
			compileReturnValueMath(rt);
			if (hasFatalError) { rt.reset(); return nullptr; }
		}
		else{
			switch (cToken->getTokenType()){
			case TokenType::Number:
				rt->addValueToVector(stod(cToken->getDescription()));
				break;
			case TokenType::BooleanTrue: case TokenType::BooleanFalse:
				rt->addValueToVector(cToken->getDescription().compare("true") == 0);
				break;
			case TokenType::Undefined:
				rt->addValueToVector(nullptr);
				break;
			default:
				rt->addValueToVector(cToken->getDescription());
			}
		}
		cToken = getNextToken();
		if (cToken == nullptr) { rt.reset(); return nullptr; }
	}
	rt->completeRPNVector();
	return rt;
}

boost::shared_ptr<ConditionCompilerToken> Compiler::compileCondition() 
{
	Token* start = nullptr;
	if (getCurrentToken()->getTokenType() == TokenType::OpenParenthesis){
		start = getCurrentToken();
	}
	if (getNextToken() == nullptr) return nullptr;
	boost::shared_ptr<ConditionCompilerToken> cct = boost::shared_ptr<ConditionCompilerToken>(new ConditionCompilerToken(compileReturnValue()));
	if (hasFatalError) {  cct.reset(); return nullptr; }
	if (getNextToken() == nullptr) {  cct.reset(); return nullptr; }
	return cct;
}

boost::shared_ptr<FunctionCompilerToken> Compiler::compileFunctionCall()
{
	bool hasException = false;
	if (!globalSymbolTable->hasFunctionSymbolWithName(getCurrentToken()->getDescription())) {
		errorList.push_back(UndefinedSymbolException(getCurrentToken()->getLineNumber(), getCurrentToken()->getLinePosition(), getCurrentToken()->getDescription(), "Function"));
		hasException = true;
	}
	Token* fTok = getCurrentToken();
	boost::shared_ptr<FunctionCompilerToken> fct(new FunctionCompilerToken(getCurrentToken()->getDescription()));
	Token* start = getNextToken();
	if (start == nullptr) { fct.reset(); return nullptr; }
	while (getCurrentToken()->getPartner() != start) {
		if ((dTok = getNextToken()) == nullptr) { fct.reset(); return nullptr; }
		if (dTok->getPartner() != start) {
			fct->addArgument(compileReturnValue());
			if (hasFatalError) { fct.reset(); return nullptr; }
		}
	}
	if (!hasException && globalSymbolTable->getFunctionSymbol(fct->getName(), fct->getArguments().size()) == nullptr) {
		errorList.push_back(UndefinedSymbolException(fTok->getLineNumber(), fTok->getLinePosition(), fTok->getDescription(), "Function"));
	}
	return fct;
}

Action* Compiler::compileStatementVar(Action* statement) 
{
	Token* sTok = getNextToken();
	if (sTok == nullptr) return nullptr;
	std::string name = sTok->getDescription();
	if ((dTok = getNextToken()) == nullptr) return nullptr;
	if (dTok->getTokenType() == TokenType::AssignmentOperator) {
		if (getNextToken() == nullptr) return nullptr;
		statement->setCompilerToken(boost::shared_ptr<AssignCompilerToken>(new AssignCompilerToken(name, compileReturnValue(), TokenType::AssignmentOperator)));
		if (hasFatalError) return nullptr;
	}
	else{
		statement = nullptr;
	}
	if(!currentSymbolTable->addSymbolToTable(name))
		errorList.push_back(SymbolAlreadyExistsException(sTok->getLineNumber(), sTok->getLinePosition(), name, "Var"));
	return statement;
}

Action* Compiler::compileStatementName(Action* statement) 
{
	Token* nTok = getCurrentToken();
	std::string name = nTok->getDescription();
	if ((dTok = peekNextToken()) == nullptr) return nullptr;
	if (dTok->getTokenType() == TokenType::OpenParenthesis){
		statement->setCompilerToken(compileFunctionCall());
		if (hasFatalError) return nullptr;
	}
	else {
		if (!(currentSymbolTable->hasSymbol(name) || globalSymbolTable->hasSymbol(name))) {
			errorList.push_back(UndefinedSymbolException(nTok->getLineNumber(), nTok->getLinePosition(), name, "Var"));
		}
		if ((dTok = getNextToken()) == nullptr) return nullptr;
		TokenType::TokenType op = dTok->getTokenType();
		if (getNextToken() == nullptr) return nullptr;
		switch (op) {
			case TokenType::AssignmentOperator: case TokenType::AddThenAssignOperator: case TokenType::MinusThenAssignOperator: case TokenType::DivideThenAssignOperator: case TokenType::MultiplyThenAssignOperator:
				statement->setCompilerToken(boost::shared_ptr<AssignCompilerToken>(new AssignCompilerToken(name, compileReturnValue(), op)));
				if (hasFatalError) return nullptr;
				break;
			case TokenType::IncreaseOperator: case TokenType::DecreaseOperator:{
				boost::shared_ptr<VarCompilerToken> v = boost::shared_ptr<VarCompilerToken>(new VarCompilerToken(name));
				v->setBackOperator(op);
				statement->setCompilerToken(v);
				break;
			}
		}
	}
	return statement;
}

void Compiler::compileReturnValueName(boost::shared_ptr<ReturnValueCompilerToken> rt)
{
	if ((dTok = peekNextToken()) == nullptr) return;
	if (dTok->getTokenType() == TokenType::OpenParenthesis){
		rt->addValueToVector(compileFunctionCall());
		if (hasFatalError) return;
	}
	else {
		if (!(currentSymbolTable->hasSymbol(getCurrentToken()->getDescription()) || globalSymbolTable->hasSymbol(getCurrentToken()->getDescription()))) {
			errorList.push_back(UndefinedSymbolException(getCurrentToken()->getLineNumber(), getCurrentToken()->getLinePosition(), getCurrentToken()->getDescription(), "Var"));
		}
		boost::shared_ptr<VarCompilerToken> v = boost::shared_ptr<VarCompilerToken>(new VarCompilerToken(getCurrentToken()->getDescription()));
		if (dTok->getTokenType() == TokenType::IncreaseOperator || dTok->getTokenType() == TokenType::DecreaseOperator){
			if (getNextToken() == nullptr) { v.reset(); return; }
			v->setBackOperator(dTok->getTokenType());
		}
		rt->addValueToVector(v);
	}
}

void Compiler::compileReturnValueIncreaseDecrease(boost::shared_ptr<ReturnValueCompilerToken> rt)
{
	if ((dTok = peekNextToken()) == nullptr) return;
	boost::shared_ptr<VarCompilerToken> v = boost::shared_ptr<VarCompilerToken>(new VarCompilerToken(dTok->getDescription()));
	v->setFrontOperator(getCurrentToken()->getTokenType());
	rt->addValueToVector(v);
	getNextToken();
}

void Compiler::compileReturnValueMath(boost::shared_ptr<ReturnValueCompilerToken> rt)
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

Action* Compiler::createAction() {
	Action* a = new Action();
	actions.push_back(a);
	return a;
}

DoNothingAction* Compiler::createDoNothing() {
	DoNothingAction* a = new DoNothingAction();
	actions.push_back(a);
	return a;
}

std::vector<std::string> Compiler::getAllFunctionAndVariableNames()
{
	std::vector<std::string> list;

	for each (FunctionSymbol* functionSymbol in globalSymbolTable->getAllFunctionSymbols())
	{
		list.push_back(functionSymbol->getName());
	}

	for each (Symbol* symbol in globalSymbolTable->getAllSymbols())
	{
		list.push_back(symbol->getName());
	}

	return list;
}