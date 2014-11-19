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
	//std::vector<SymbolTable*> symbolTables;

	//Token* currentToken;

	// main compile methods
	void compileFunction();
	void compileCodeBlock();
	void compileStatement();
	void compileWhile();
	void compileIf();
	Action* compileElse();
	// compileReturnValue cannot handle return values that should be compiled as a condition and then returned.
	// Need to create a private (sub)function that handles this behaviour.
	ReturnValueCompilerToken* compileReturnValue();
	ConditionCompilerToken* compileCondition();
	SubConditionCompilerToken* compileSubCondition();
	FunctionCompilerToken* compileFunctionCall();

	// submethods for compile methods
	Action* compileStatementVar(Action*);
	Action* compileStatementName(Action*);
	void compileReturnValueName(ReturnValueCompilerToken*);
	void compileReturnValueIncreaseDecrease(ReturnValueCompilerToken*);
	void compileReturnValueMath(ReturnValueCompilerToken*);

	Token* getCurrentToken();
	Token* getNextToken();
	Token* peekNextToken();
	void eraseCurrentToken();
	void resetTokenIter();

	void addInternalFunctions();

	//bool addNewVariable(int level, string functionname, string name);
};

