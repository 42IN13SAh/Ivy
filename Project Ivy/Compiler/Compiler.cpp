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
}


void Compiler::compile() {
	// Init all vars on level 0
	while (tokenIter != tokenList.end()) {
		if (getCurrentToken()->getLevel() == 0 && getCurrentToken()->getTokenType() == Var)
			compileStatement();
		else
			tokenIter++;
	}

	resetTokenIter();
	// Compile all functions
	while (tokenIter != tokenList.end()) {
		if (getCurrentToken()->getLevel() == 0 && getCurrentToken()->getTokenType() == Function)
			compileFunction();
		else
			tokenIter++;
	}
}

void Compiler::compileFunction() {
	// Compile function arguments and name

	// compileCodeBlock
	compileCodeBlock();
}

void Compiler::compileCodeBlock() {
	//Token* startToken = getCurrentToken();

	// Check if token is If or While, else compileStatement
	while (getCurrentToken()->getTokenType() != ClosingBracket) {
		Action* last = lastAction;
		switch (getCurrentToken()->getTokenType()) {
			case WhileStatement:
				compileWhile();
				break;
			case IfStatement:
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
	switch (getCurrentToken()->getTokenType()) {
	case Var:
	{
		std::string name = getNextToken()->getDescription();
		if (getNextToken()->getTokenType() == AssignmentOperator){
			AssignCompilerToken* act = new AssignCompilerToken(name, compileReturnValue());
			statement->setCompilerToken(act);
		}
		else{
			statement = nullptr;
		}
		symbolTable->addSymbolToTable(name);
		break;
	}
	case Name:
		// Check next token, if '(' make function call
		// else
		// Check if variable name already exists, create assignment if '='|'+='|'-='|'\='|'*=' is next in line
		// Do other if ++|-- is next inline, see inc|dec operators, return -> up or down -> assign value
		if (peekNextToken()->getTokenType() == OpenParenthesis){

		}else{

		}
		break;
	case Return:
		// Check next:
		// Open '(' Create Condition line, ? can it be a condition without '(' ?
		// Var name or Func name
		// See options Var token
		break;
	case IncreaseOperator:
	case DecreaseOperator:
		// Check if next Name token exists in vars, get var value -> count up or down -> assign -> return
		break;
	}
	if (statement != nullptr){
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

}

void Compiler::compileIfElse() {

}

// Return must be RValueCompToken
ReturnValueCompilerToken* Compiler::compileReturnValue() {
	bool hasBracketAtStart = (getCurrentToken()->getTokenType() == OpenParenthesis);
	TokenType endTypes[] = {LineEnd /*, All condition operators */};
	int endSize = 1;
	ReturnValueCompilerToken* rt = new ReturnValueCompilerToken();
	while (find(endTypes, endTypes+endSize,getCurrentToken()->getTokenType()) != endTypes+endSize) {
		if (getCurrentToken()->getTokenType() == Name) {
			if (peekNextToken()->getTokenType() == OpenParenthesis) {
				rt->addValueToVector(compileFunctionCall());
			} else {
				rt->addValueToVector(new VarCompilerToken(getCurrentToken()->getDescription()));
			}
		} else if (getCurrentToken()->getParentType() == MathOperator || getCurrentToken()->getTokenType() == OpenParenthesis || getCurrentToken()->getTokenType() == ClosingParenthesis) {
			switch (getCurrentToken()->getTokenType()) {
				case OpenParenthesis: case AddOperator: case MinusOperator:
					rt->pushOperatorToStack(getCurrentToken()->getTokenType());
					break;
				case MultiplyOperator: case DivideOperator: case ModuloOperator:
				{
					TokenType tmp = rt->peekOperatorStack();
					if (tmp == MultiplyOperator || tmp == DivideOperator || tmp == ModuloOperator) {
						rt->addValueToVector(tmp);
						rt->popOperatorStack();
					}
					rt->pushOperatorToStack(getCurrentToken()->getTokenType());
					break;
				}
				case ClosingParenthesis:
					while (rt->peekOperatorStack() != OpenParenthesis) {
						rt->addValueToVector(rt->peekOperatorStack());
						rt->popOperatorStack();
					}
					rt->popOperatorStack();
					break;
			}
		} else {
			rt->addValueToVector(getCurrentToken()->getDescription());
		}
		getNextToken();
	}
	rt->completeRPNVector();
	return rt;
}

FunctionCompilerToken* Compiler::compileFunctionCall() {
	FunctionCompilerToken* fct = new FunctionCompilerToken(getCurrentToken()->getDescription());
	getNextToken();
	Token* start = getCurrentToken()->getPartner();
	getNextToken();
	while (getCurrentToken()->getPartner() == start && getCurrentToken()->getTokenType() != ClosingParenthesis) {
		fct->addArgument(compileReturnValue());
		getNextToken();
	}
	return fct;
}


Token* Compiler::getCurrentToken() { return *tokenIter; }
Token* Compiler::getNextToken() { return *++tokenIter; }
Token* Compiler::peekNextToken() { return *tokenIter+1; }
void Compiler::resetTokenIter() { tokenIter = tokenList.begin(); }

