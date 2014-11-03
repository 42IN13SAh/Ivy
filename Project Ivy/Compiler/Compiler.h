#pragma once
#include <vector>
#include <map>
#include <list>
#include <stack>
#include "SymbolTable.h"
#include "Action.h"
#include "DoNothingAction.h"
#include "ReturnValueCompilerToken.h"
#include "FunctionCompilerToken.h"
#include "VarCompilerToken.h"
#include "AssignCompilerToken.h"
#include "ConditionCompilerToken.h"
#include "SubConditionCompilerToken.h"

#include "../Tokenizer/Token.h"

class Compiler
{
public:
	Compiler(std::list<Token*>);
	~Compiler();

	void compile();
	Action* getFirstAction();
	SymbolTable* getSymbolTable();

private:
	std::list<Token*> tokenList;

	Action* firstAction;
	Action* lastAction;
	SymbolTable* symbolTable;
	std::list<Token*>::iterator tokenIter;
	std::vector<SymbolTable*> symbolTables;

	//Token* currentToken;

	// private functions for compiling
	void compileFunction();
	void compileCodeBlock();
	void compileStatement();
	void compileWhile();
	void compileIf();
	Action* compileElse();
	ReturnValueCompilerToken* compileReturnValue(); // Return must be RValueCompToken
	ConditionCompilerToken* compileCondition();
	SubConditionCompilerToken* compileSubCondition();
	FunctionCompilerToken* compileFunctionCall();


	Token* getCurrentToken();
	Token* getNextToken();
	Token* peekNextToken();
	void eraseCurrentToken();
	void resetTokenIter();

	//bool addNewVariable(int level, string functionname, string name);
};

