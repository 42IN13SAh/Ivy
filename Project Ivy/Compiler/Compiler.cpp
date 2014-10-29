#include "Compiler.h"


Compiler::Compiler(list<Token*> tokenList)
{
	this->tokenList = tokenList;
}

void Compiler::compileStatement(Token* startToken) {
	// Check start until lineend Token
	switch (startToken->getTokenType()) {
	case Var:
		// Create var, and assignment if '=' is inside the line
		// Options: Number, String, Sum (math operators), String + String, StatementLine (Boolean), None (undefined type)
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
		// Open '(' Create Statement line, ? can it be a statement without '(' ?
		// Var name or Func name
		// See options Var token
		break;
	case IncreaseOperator:
	case DecreaseOperator:
		// Check if next Name token exists in vars, get var value -> count up or down -> assign -> return
		break;
	}
}

Compiler::~Compiler()
{
}

//Temporal main function for testing:
int main(){

	return 0;
}