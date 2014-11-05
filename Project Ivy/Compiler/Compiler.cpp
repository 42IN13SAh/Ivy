#include "Compiler.h"


Compiler::Compiler(list<Token*> tokenList)
{
	this->tokenList = tokenList;
	this->firstAction = new DoNothingAction();
	this->lastAction = firstAction;
	this->symbolTable = new SymbolTable();
	resetTokenIter();
}

Compiler::~Compiler()
{
	//delete firstAction;
	//delete lastAction;
	//delete symbolTable;
}


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

void Compiler::compileStatement() {
	// Check start until lineend Token
	Action* statement = new Action();
	Token* t = getCurrentToken();
	switch (t->getTokenType()) {
	case TokenType::Var:
	{
		// Set scope for variable/action
		std::string name = getNextToken()->getDescription();
		if (getNextToken()->getTokenType() == TokenType::AssignmentOperator){
			statement->setCompilerToken(new AssignCompilerToken(name, compileReturnValue()));
		} else {
			statement = nullptr;
		}

		//A variable may not be declared twice with the same name
		if (symbolTable->hasSymbol(name)) {
			throw new exception; //TODO: better exception handling. 
		}
		else {
			symbolTable->addSymbolToTable(name);
		}
		break;
	}
	case TokenType::Name:
	{
		// Check if variable name already exists, create assignment if '='|'+='|'-='|'\='|'*=' is next in line
		std::string name = getCurrentToken()->getDescription();
		if (peekNextToken()->getTokenType() == TokenType::OpenParenthesis){
			statement->setCompilerToken(compileFunctionCall());
		}
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
		break;
	}
	case TokenType::Return:
		getNextToken();
		statement->setCompilerToken(compileReturnValue());
		break;
	case TokenType::IncreaseOperator: case TokenType::DecreaseOperator:
		statement->setCompilerToken(compileReturnValue());
		break;
	}
	if (statement != nullptr && statement->getCompilerToken() != nullptr){
		lastAction->setNextAction(statement);
		statement->setNextAction(new DoNothingAction());
		lastAction = statement->getNextAction();
	}
}

void Compiler::compileWhile()
{
	Action* begin = lastAction;
	Action* condition = new Action();
	// Compile condition
	condition->setCompilerToken(compileCondition());
	lastAction->setNextAction(condition);

	DoNothingAction* onTrue = new DoNothingAction();
	condition->setNextAction(onTrue);

	/*Action* statement = new Action();
	onTrue->setNextAction(statement);*/
	// Compile statement
	compileCodeBlock();
	onTrue->setNextAction(lastAction);
	lastAction->setNextAction(begin);

	DoNothingAction* onFalse = new DoNothingAction();
	condition->setFalseAction(onFalse);

	lastAction = onFalse;
}

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

Action* Compiler::compileElse() {
	DoNothingAction* elseAction = new DoNothingAction();
	
	compileCodeBlock();
	
	return elseAction;
}

// Return must be RValueCompToken
ReturnValueCompilerToken* Compiler::compileReturnValue() {
	bool hasBracketAtStart = (getCurrentToken()->getTokenType() == TokenType::OpenParenthesis);
	//TokenType endTypes[] = { TokenType::LineEnd /*, All condition operators */ };
	//int endSize = 1;
	Token* start = getCurrentToken();
	if (start->getTokenType() == TokenType::OpenParenthesis)
		getNextToken();
	//TODO: ++x en x++ werken nog niet!!
	ReturnValueCompilerToken* rt = new ReturnValueCompilerToken();
	while (getCurrentToken()->getTokenType() != TokenType::LineEnd && getCurrentToken()->getPartner() != start && getCurrentToken()->getTokenType() != TokenType::ParameterOperator) {
		if (getCurrentToken()->getTokenType() == TokenType::Name) {
			if (peekNextToken()->getTokenType() == TokenType::OpenParenthesis) {
				rt->addValueToVector(compileFunctionCall());
			} else {
				VarCompilerToken* v = new VarCompilerToken(getCurrentToken()->getDescription());
				if (peekNextToken()->getTokenType() == TokenType::IncreaseOperator || peekNextToken()->getTokenType() == TokenType::DecreaseOperator)
					v->setBackOperator(getNextToken()->getTokenType());
				rt->addValueToVector(v);
			}
		} else if (getCurrentToken()->getTokenType() == TokenType::IncreaseOperator || getCurrentToken()->getTokenType() == TokenType::DecreaseOperator) {
			// Token is undefined or something, it doesnt say null on the token but the token has invalid fields
			// bad_memory_alloc
			VarCompilerToken* v = new VarCompilerToken(peekNextToken()->getDescription());
			v->setFrontOperator(getCurrentToken()->getTokenType());
			rt->addValueToVector(v);
			getNextToken();
		} else if (getCurrentToken()->getParentType() == ParentType::MathOperator || getCurrentToken()->getTokenType() == TokenType::OpenParenthesis || getCurrentToken()->getTokenType() == TokenType::ClosingParenthesis) {
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
		else if (getCurrentToken()->getTokenType() != TokenType::AssignmentOperator) {
			rt->addValueToVector(getCurrentToken()->getDescription());
		}
		getNextToken();
	}
	rt->completeRPNVector();
	return rt;
}

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

FunctionCompilerToken* Compiler::compileFunctionCall() {
	FunctionCompilerToken* fct = new FunctionCompilerToken(getCurrentToken()->getDescription());
	Token* start = getNextToken();
	while (getCurrentToken()->getPartner() != start && getCurrentToken()->getTokenType() != TokenType::ClosingParenthesis) {
		fct->addArgument(compileReturnValue());
	}
	return fct;
}

void Compiler::addInternalFunctions() {
	// magic
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