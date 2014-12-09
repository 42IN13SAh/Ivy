#ifdef COMPILER_EXPORTS
#define COMPILER_API __declspec(dllexport) 
#else
#define COMPILER_API __declspec(dllimport) 
#endif
#pragma once
#include <vector>
#include <map>
#include <list>
#include <stack>
#include "Token.h"
#include "SymbolTable.h"
#include "Action.h"
#include "DoNothingAction.h"
#include "ReturnValueCompilerToken.h"
#include "FunctionCompilerToken.h"
#include "VarCompilerToken.h"
#include "AssignCompilerToken.h"
#include "ConditionCompilerToken.h"
#include "ReturnCompilerToken.h"

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
	SymbolTable* globalSymbolTable;
	SymbolTable* currentSymbolTable;
	std::list<Token*>::iterator tokenIter;
	void compileFunction();
	void addFunctionSignature();
	void compileCodeBlock();
	void compileStatement();
	void compileWhile();
	void compileIf();
	Action* compileElse();
	ReturnValueCompilerToken* compileReturnValue();
	ConditionCompilerToken* compileCondition();
	FunctionCompilerToken* compileFunctionCall();
	Action* compileStatementVar(Action*);
	Action* compileStatementName(Action*);
	void compileReturnValueName(ReturnValueCompilerToken*);
	void compileReturnValueIncreaseDecrease(ReturnValueCompilerToken*);
	void compileReturnValueMath(ReturnValueCompilerToken*);
	Token* getCurrentToken();
	Token* getNextToken();
	Token* peekNextToken();
	void resetTokenIter();
	void addInternalFunctions();
};

