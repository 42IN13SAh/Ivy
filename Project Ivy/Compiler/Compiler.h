#pragma once
#include <vector>
#include <list>
#include <stack>
#include "SymbolTable.h"
#include "Action.h"
#include "DoNothingAction.h"
#include "ReturnValueCompilerToken.h"
#include "FunctionCompilerToken.h"
#include "VarCompilerToken.h"
#include "AssignCompilerToken.h"

#include "../Tokenizer/Token.h"

using namespace std;
class Compiler
{
public:
	Compiler(list<Token*>);
	~Compiler();

	void compile();

private:
	list<Token*> tokenList;

	Action* firstAction;
	Action* lastAction;
	SymbolTable* symbolTable;
	std::list<Token*>::iterator tokenIter;
	//Token* currentToken;

	// private functions for compiling
	void compileFunction();
	void compileCodeBlock();
	void compileStatement();
	void compileWhile();
	void compileIf();
	void compileIfElse();
	ReturnValueCompilerToken* compileReturnValue(); // Return must be RValueCompToken
	FunctionCompilerToken* compileFunctionCall();


	Token* getCurrentToken();
	Token* getNextToken();
	Token* peekNextToken();
	void eraseCurrentToken();
	void resetTokenIter();
};

