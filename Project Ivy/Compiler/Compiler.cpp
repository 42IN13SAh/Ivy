#include "Compiler.h"


Compiler::Compiler(list<Token*> tokenList)
{
	this->tokenList = tokenList;
	this->firstAction = new DoNothingAction();
	this->lastAction = firstAction;

	resetTokenIter();
}

Compiler::~Compiler()
{
}

void Compiler::compile() {
	// Init all vars on level 0
	compileFirstVars();
	// Compile all functions
	while (tokenIter != tokenList.end()) {
		if (getCurrentToken()->getLevel == 0 && getCurrentToken()->getTokenType() == Function) {
			compileFunction();
		}
	}
}

void Compiler::compileFirstVars() {
	while (tokenIter != tokenList.end()) {
		if (getCurrentToken()->getLevel() == 0 && getCurrentToken()->getTokenType() == Var)
			compileStatement();
		else
			tokenIter++;
	}

	resetTokenIter();
}

void Compiler::compileFunction() {
	// Compile function arguments and name

	// compileMultiStatement
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
			eraseCurrentToken();
	}
}

void Compiler::compileStatement() {
	// Check start until lineend Token
	Action* statement = new Action();
	switch (getCurrentToken()->getTokenType()) {
	case Var:
		// Create var, and assignment if '=' is inside the line
		// Options: Number, String, Sum (math operators), String + String, ConditionLine (Boolean), None (undefined type)
		// ^ using Var name or Func name ^
		break;
	case Name:
		// Check next token, if '(' make function call
		// else
		// Check if variable name already exists, create assignment if '='|'+='|'-='|'\='|'*=' is next in line
		// Do other if ++|-- is next inline, see inc|dec operators, return -> up or down -> assign value
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
	lastAction->setNextAction(statement);
	statement->setNextAction(new DoNothingAction());
	lastAction = statement->getNextAction();
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

// Return must be RValueCompToken
CompilerToken* Compiler::compileReturnValue() {
	bool hasBracketAtStart = (getCurrentToken()->getTokenType() == OpenParenthesis);
	TokenType endTypes[] = {LineEnd /*, All condition operators */};
	int endSize = 1;

	while (find(endTypes, endTypes+endSize,getCurrentToken()->getTokenType()) != endTypes+endSize) {
		switch (getCurrentToken()->getTokenType()) {
		case Number:
		case String:
			if (peekNextToken()->getParentType() == MathOperator) {
				// give rvalue a sum, this = left value
			} else {
				// set rvalue result, expecting end of rvalue
			}
			break;
		case Name:
			// Function or Var, check if exists first
			if (peekNextToken()->getTokenType() == OpenParenthesis) {
				// Function
				// Get function arg nr and execute compileRValue for each argument
			} else {
				// Var
				// Get var value and set it in the right spot, see Number and String (make function for this behaviour)
			}
			break;
		/*case MathOperators:
			break;*/
		case OpenParenthesis:
			break;
		case ClosingParenthesis:
			// Possible end of RValue
			break;
		}

		getNextToken();
	}

	return nullptr;
}

Token* Compiler::getCurrentToken() { return *tokenIter; }
Token* Compiler::getNextToken() { tokenIter = tokenList.erase(tokenIter); return *tokenIter; }
Token* Compiler::peekNextToken() { return *tokenIter+1; }
void Compiler::eraseCurrentToken() { tokenIter = tokenList.erase(tokenIter); }
void Compiler::resetTokenIter() { tokenIter = tokenList.begin(); }

//Temporal main function for testing:
int main(){

	return 0;
}