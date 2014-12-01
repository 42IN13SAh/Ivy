#include "Compiler.h"
//#include "../Virtual Machine/IInternalFunction.h"
#include <memory>

Compiler::Compiler(list<Token*> tokenList) {
	this->tokenList = tokenList;
	this->firstAction = new DoNothingAction();
	this->lastAction = firstAction;
	this->globalSymbolTable = new SymbolTable();
	resetTokenIter();
}

Compiler::~Compiler() {
	//delete firstAction;
	//delete lastAction;
	//delete symbolTable;
}

/// Main compile function.
/// Adds internal functions and starts the compiling process.
void Compiler::compile() {
	currentSymbolTable = globalSymbolTable;

	addInternalFunctions();

	// Init all vars and function names on level 0
	while (tokenIter != tokenList.end()) {
		if (getCurrentToken()->getTokenType() == TokenType::Function)
			addFunctionSignature();
		else if (getCurrentToken()->getLevel() == 0 && (getCurrentToken()->getTokenType() == TokenType::Var || getCurrentToken()->getTokenType() == TokenType::Name))
			compileStatement();
		else
			tokenIter++;
	}

	resetTokenIter();

	// Compile all functions
	while (tokenIter != tokenList.end()) {
		if (getCurrentToken()->getLevel() == 0 && getCurrentToken()->getTokenType() == TokenType::Function)
			compileFunction();
		else
			tokenIter++;
	}
}

/// Compiles entire functions.
/// Called by the compile function.
void Compiler::compileFunction() {
	// Compile function arguments and name
	Action* function = new Action(); // startFunction
	FunctionCompilerToken* fct = new FunctionCompilerToken(getNextToken()->getDescription());
	Token* start = getNextToken();

	while (getCurrentToken()->getPartner() != start) {
		if (getCurrentToken()->getTokenType() == TokenType::Name) {
			fct->addArgumentName(getCurrentToken()->getDescription());
		}
		getNextToken();
	}

	getNextToken();

	function->setCompilerToken(fct);
	function->setNextAction(new DoNothingAction());

	lastAction = function->getNextAction();

	FunctionSymbol* functionSymbol = currentSymbolTable->getFunctionSymbol(fct->getName(), fct->getArgumentNames().size());
	functionSymbol->setStartAction(function);

	currentSymbolTable = functionSymbol->getSymbolTable();
	compileCodeBlock(); // lastAction = endFunction
	currentSymbolTable = globalSymbolTable;

	functionSymbol->setEndAction(lastAction);
}

void Compiler::addFunctionSignature() {
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

/// Compiles codeblocks.
/// Called by compileFunction.
void Compiler::compileCodeBlock() {
	// Check if token is If or While, else compileStatement
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
				// TODO: better exception handling for this function in function case.
				throw new exception;
				break;
			default:
				compileStatement();
				break;
		}
		if (last == lastAction)
			getNextToken();
	}
}

/// Compiles a single line statement.
/// Called by compileCodeBlock.
void Compiler::compileStatement() {
	// Check start until lineend Token
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
			statement->setCompilerToken(compileReturnValue());
			break;
	}

	if (statement != nullptr && statement->getCompilerToken() != nullptr) {
		lastAction->setNextAction(statement);
		statement->setNextAction(new DoNothingAction());
		lastAction = statement->getNextAction();
	}
}

/// Compiles a while statement.
/// Called by compileCodeBlock.
void Compiler::compileWhile() {
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

/// Compiles an if statement.
/// If the if contains an else it will call the compileElse function too.
/// Called by compileCodeBlock.
void Compiler::compileIf() {
	Token* start = getCurrentToken();
	
	Action* ifAction = new Action();
	Action* end = new DoNothingAction();

	getNextToken();

	ifAction->setCompilerToken(compileCondition());
	ifAction->setNextAction(new DoNothingAction());
	lastAction->setNextAction(ifAction);
	lastAction = ifAction->getNextAction();

	compileCodeBlock();

	if (start->getPartner() != nullptr && start->getPartner()->getTokenType() == TokenType::ElseStatement)
		ifAction->setFalseAction(compileElse());
	else
		ifAction->setFalseAction(end);

	lastAction->setNextAction(end);
	lastAction = end;
}

/// Compiles an else statement.
/// Called by compileIf.
/// Returns the first Action of the else Action sequence.
Action* Compiler::compileElse() {
	DoNothingAction* elseAction = new DoNothingAction();
	lastAction = elseAction;
	getNextToken();
	compileCodeBlock();
	
	return elseAction;
}

/// Compiles a return value.
/// A return value is any calculation or sequence that returns a value.
/// Returns a Token containing the calculation in RPN notation.
ReturnValueCompilerToken* Compiler::compileReturnValue() {
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
			rt->addValueToVector(cToken->getDescription());
		}
		cToken = getNextToken();
	}
	rt->completeRPNVector();

	return rt;
}

/// Compiles a condition.
/// A condition can be resolved into true or false.
/// This method will split the entire condition into small parts called subconditions.
/// Returns a Token containing subconditions and TokenTypes (operators).
ConditionCompilerToken* Compiler::compileCondition() {
	Token* start = nullptr;

	if (getCurrentToken()->getTokenType() == TokenType::OpenParenthesis)
		start = getCurrentToken();

	getNextToken();

	ConditionCompilerToken* cct = new ConditionCompilerToken(compileReturnValue());
	getNextToken();
	return cct;
}

/// Compiles a subcondition.
/// A subcondition is the smallest possible part of a condition containing two values
/// and a operator that compares them.
/// Returns a Token containing these two values and a operator type.

// TODO: this function is deprecated
SubConditionCompilerToken* Compiler::compileSubCondition() {
	SubConditionCompilerToken* sc = new SubConditionCompilerToken();
	sc->setLeft(compileReturnValue());

	if (getCurrentToken()->getParentType() == ParentType::SubConditionOperator) {
		sc->setOperator(getCurrentToken()->getTokenType());

		getNextToken();

		sc->setRight(compileReturnValue());
	}

	return sc;
}

/// Compiles a function call.
/// Returns a Token with the methods name and it's parameters.
FunctionCompilerToken* Compiler::compileFunctionCall() {
	FunctionCompilerToken* fct = new FunctionCompilerToken(getCurrentToken()->getDescription());

	Token* start = getNextToken();

	while (getCurrentToken()->getPartner() != start) {
		
		if (getNextToken()->getPartner() != start)
			fct->addArgument(compileReturnValue());
	}
	getNextToken();

	return fct;
}

/// Subfunctions

/// Compiles a var within a statement.
/// Called by compileStatement.
Action* Compiler::compileStatementVar(Action* statement) {
	// Set scope for variable/action
	std::string name = getNextToken()->getDescription();

	if (getNextToken()->getTokenType() == TokenType::AssignmentOperator) {
		getNextToken();
		statement->setCompilerToken(new AssignCompilerToken(name, compileReturnValue(), TokenType::AssignmentOperator));
	} else
		statement = nullptr;

	//A variable may not be declared twice with the same name
	if (currentSymbolTable->hasSymbol(name))
		throw new exception; //TODO: better exception handling. 
	else
		currentSymbolTable->addSymbolToTable(name);

	return statement;
}

/// Compiles a name within a statement.
/// Called by compileStatement.
Action* Compiler::compileStatementName(Action* statement) {
	// Check if variable name already exists, create assignment if '='|'+='|'-='|'\='|'*=' is next in line
	std::string name = getCurrentToken()->getDescription();

	if (peekNextToken()->getTokenType() == TokenType::OpenParenthesis)
		statement->setCompilerToken(compileFunctionCall());
	else if (currentSymbolTable->hasSymbol(name) || globalSymbolTable->hasSymbol(name)) {
		TokenType op = getNextToken()->getTokenType();
		getNextToken();
		switch (op) {
			case TokenType::AssignmentOperator: case TokenType::AddThenAssignOperator: case TokenType::MinusThenAssignOperator: case TokenType::DivideThenAssignOperator: case TokenType::MultiplyThenAssignOperator:
				statement->setCompilerToken(new AssignCompilerToken(name, compileReturnValue(), op));
				break;
			case TokenType::IncreaseOperator: case TokenType::DecreaseOperator:
				statement->setCompilerToken(compileReturnValue());
				break;
		}
	}

	return statement;
}

/// Compiles a name within a return value.
/// Called by compileReturnValue.
void Compiler::compileReturnValueName(ReturnValueCompilerToken* rt) {
	if (peekNextToken()->getTokenType() == TokenType::OpenParenthesis)
		rt->addValueToVector(compileFunctionCall());
	else {
		VarCompilerToken* v = new VarCompilerToken(getCurrentToken()->getDescription());

		if (peekNextToken()->getTokenType() == TokenType::IncreaseOperator || peekNextToken()->getTokenType() == TokenType::DecreaseOperator)
			v->setBackOperator(getNextToken()->getTokenType());

		rt->addValueToVector(v);
	}
}

/// Compiles the increase and decrease operator within a return value.
/// Called by compileReturnValue.
void Compiler::compileReturnValueIncreaseDecrease(ReturnValueCompilerToken* rt) {
	// Token is undefined or something, it doesnt say null on the token but the token has invalid fields
	// bad_memory_alloc
	VarCompilerToken* v = new VarCompilerToken(peekNextToken()->getDescription());
	v->setFrontOperator(getCurrentToken()->getTokenType());
	rt->addValueToVector(v);

	getNextToken();
}

/// Compiles any math within a return value.
/// Called by compileReturnValue.
void Compiler::compileReturnValueMath(ReturnValueCompilerToken* rt) {
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
			rt->addValueToVector(rt->peekOperatorStack());
			rt->popOperatorStack();
		}
		rt->pushOperatorToStack(getCurrentToken()->getTokenType());
	}
	else if (getCurrentToken()->getParentType() == ParentType::ConditionOperator){
		if (!rt->isEmpty()){
			rt->addValueToVector(rt->peekOperatorStack());
			rt->popOperatorStack();
		}
		rt->addValueToVector(getCurrentToken()->getTokenType());
	}
}

/// Adds internal functions to the compiler.
void Compiler::addInternalFunctions() {
	
	/*std::shared_ptr<IInternalFunction> x = InternalFunctionFactory::Instance()->Create("pow");
	x->Execute({ 2.0, 3.0 });*/

	for each(auto iter in InternalFunctionFactory::Instance()->GetArgNrMap()) {
		currentSymbolTable->addFunctionSymbol(new FunctionSymbol(iter.first, iter.second, nullptr, nullptr, true));
	}
	
	// TODO: read internal functions from a file or list
	//currentSymbolTable->addFunctionSymbol(new FunctionSymbol("print", 1, nullptr, nullptr, true));
}

Token* Compiler::getCurrentToken() { return *tokenIter; }
Token* Compiler::getNextToken() { return (tokenIter != tokenList.end()) ? *++tokenIter : nullptr; }

Token* Compiler::peekNextToken() { 
	Token* temp = getNextToken();
	tokenIter--;
	return temp;
}

void Compiler::resetTokenIter() { tokenIter = tokenList.begin(); }
Action* Compiler::getFirstAction() { return firstAction; }
SymbolTable* Compiler::getSymbolTable() { return globalSymbolTable; }