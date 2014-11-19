#include "Compiler.h"

Compiler::Compiler(list<Token*> tokenList) {
	this->tokenList = tokenList;
	this->firstAction = new DoNothingAction();
	this->lastAction = firstAction;
	this->symbolTable = new SymbolTable();
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
	addInternalFunctions();

	// Init all vars on level 0
	while (tokenIter != tokenList.end()) {
		if (getCurrentToken()->getLevel() == 0 && (getCurrentToken()->getTokenType() == TokenType::Var || getCurrentToken()->getTokenType() == TokenType::Name))
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
	// compileCodeBlock
	compileCodeBlock(); // lastAction = endFunction
	symbolTable->addFunctionSymbol(new FunctionSymbol(fct->getName(), fct->getArgumentNames().size(), function, lastAction, false));
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

			statement->setCompilerToken(compileReturnValue());
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
	Action* begin = lastAction;
	Action* condition = new Action();

	condition->setCompilerToken(compileCondition());
	lastAction->setNextAction(condition);

	DoNothingAction* onTrue = new DoNothingAction();
	condition->setNextAction(onTrue);

	compileCodeBlock();

	onTrue->setNextAction(lastAction);
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
	lastAction = ifAction->getNextAction();

	compileCodeBlock();

	if (start->getPartner()->getTokenType() == TokenType::ElseStatement)
		ifAction->setFalseAction(compileElse());

	lastAction->setNextAction(end);
	lastAction = end;
}

/// Compiles an else statement.
/// Called by compileIf.
/// Returns the first Action of the else Action sequence.
Action* Compiler::compileElse() {
	DoNothingAction* elseAction = new DoNothingAction();
	lastAction = elseAction;
	
	compileCodeBlock();
	
	return elseAction;
}

/// Compiles a return value.
/// A return value is any calculation or sequence that returns a value.
/// Returns a Token containing the calculation in RPN notation.
ReturnValueCompilerToken* Compiler::compileReturnValue() {
	bool hasBracketAtStart = (getCurrentToken()->getTokenType() == TokenType::OpenParenthesis);
	// TokenType endTypes[] = { TokenType::LineEnd /*, All condition operators */ };
	Token* start = getCurrentToken();

	if (start->getTokenType() == TokenType::OpenParenthesis)
		getNextToken();

	//TODO: ++x en x++ werken nog niet!!
	ReturnValueCompilerToken* rt = new ReturnValueCompilerToken();
	while (getCurrentToken()->getTokenType() != TokenType::LineEnd && getCurrentToken()->getPartner() != start && getCurrentToken()->getTokenType() != TokenType::ParameterOperator) {
		if (getCurrentToken()->getTokenType() == TokenType::Name)
			compileReturnValueName(rt);
		else if (getCurrentToken()->getTokenType() == TokenType::IncreaseOperator || getCurrentToken()->getTokenType() == TokenType::DecreaseOperator)
			compileReturnValueIncreaseDecrease(rt);
		else if (getCurrentToken()->getParentType() == ParentType::MathOperator || getCurrentToken()->getTokenType() == TokenType::OpenParenthesis || getCurrentToken()->getTokenType() == TokenType::ClosingParenthesis)
			compileReturnValueMath(rt);
		else if (getCurrentToken()->getTokenType() != TokenType::AssignmentOperator)
			rt->addValueToVector(getCurrentToken()->getDescription());

		getNextToken();
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

	std::vector<TokenType> cOpVector;
	std::vector<SubConditionCompilerToken*> scVector;

	while (getCurrentToken()->getPartner() != start) {
		switch (getCurrentToken()->getParentType()) {
			case ParentType::ConditionOperator:
				cOpVector.push_back(getCurrentToken()->getTokenType());
				break;
			default:
				scVector.push_back(compileSubCondition());
				break;
		}

		getNextToken();
	}
	return new ConditionCompilerToken(cOpVector, scVector);
}

/// Compiles a subcondition.
/// A subcondition is the smallest possible part of a condition containing two values
/// and a operator that compares them.
/// Returns a Token containing these two values and a operator type.
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

	while (getCurrentToken()->getPartner() != start && getCurrentToken()->getTokenType() != TokenType::ClosingParenthesis)
		fct->addArgument(compileReturnValue());

	return fct;
}

/// Subfunctions

/// Compiles a var within a statement.
/// Called by compileStatement.
Action* Compiler::compileStatementVar(Action* statement) {
	// Set scope for variable/action
	std::string name = getNextToken()->getDescription();

	if (getNextToken()->getTokenType() == TokenType::AssignmentOperator)
		statement->setCompilerToken(new AssignCompilerToken(name, compileReturnValue()));
	else
		statement = nullptr;

	//A variable may not be declared twice with the same name
	if (symbolTable->hasSymbol(name))
		throw new exception; //TODO: better exception handling. 
	else
		symbolTable->addSymbolToTable(name);

	return statement;
}

/// Compiles a name within a statement.
/// Called by compileStatement.
Action* Compiler::compileStatementName(Action* statement) {
	// Check if variable name already exists, create assignment if '='|'+='|'-='|'\='|'*=' is next in line
	std::string name = getCurrentToken()->getDescription();

	if (peekNextToken()->getTokenType() == TokenType::OpenParenthesis)
		statement->setCompilerToken(compileFunctionCall());
	else if (symbolTable->hasSymbol(name)) {
		switch (peekNextToken()->getTokenType()) {
		case TokenType::AssignmentOperator:
			statement->setCompilerToken(new AssignCompilerToken(name, compileReturnValue()));
			break;
		case TokenType::AddThenAssignOperator:
			break;
		case TokenType::MinusThenAssignOperator:
			break;
		case TokenType::DivideThenAssignOperator:
			break;
		case TokenType::MultiplyThenAssignOperator:
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
	switch (getCurrentToken()->getTokenType()) {
		case TokenType::OpenParenthesis:
			rt->pushOperatorToStack(getCurrentToken()->getTokenType());
			break;
		case TokenType::MultiplyOperator: case TokenType::DivideOperator: case TokenType::ModuloOperator: case TokenType::AddOperator: case TokenType::MinusOperator:
		{
			TokenType tmp = rt->peekOperatorStack();

			if (tmp == TokenType::MultiplyOperator || tmp == TokenType::DivideOperator || tmp == TokenType::ModuloOperator) {
				rt->addValueToVector(tmp);
				rt->popOperatorStack();
			}

			rt->pushOperatorToStack(getCurrentToken()->getTokenType());
			break;
		}
		case TokenType::ClosingParenthesis:
			// Inf loop on temp is true
			while (rt->peekOperatorStack() != TokenType::OpenParenthesis && rt->peekOperatorStack() != TokenType::Null) {
				rt->addValueToVector(rt->peekOperatorStack());
				rt->popOperatorStack();
			}

			rt->popOperatorStack();
			break;
	}
}

/// Adds internal functions to the compiler.
void Compiler::addInternalFunctions() {
	// TODO: read internal functions from a file or list
	symbolTable->addFunctionSymbol(new FunctionSymbol("print", 1, nullptr, nullptr, true));
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
SymbolTable* Compiler::getSymbolTable() { return symbolTable;  }