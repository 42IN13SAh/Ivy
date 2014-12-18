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

// Exceptions
#include "UnexpectedEndOfFileException.h"

class Compiler
{
public:
	Compiler(std::list<Token*>);
	~Compiler();
	void compile();
	Action* getFirstAction();
	SymbolTable* getSymbolTable();
	const std::vector<BaseException>& getErrorList();
private:
	bool hasFatalError;
	Token* dTok;
	std::vector<BaseException> errorList;
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
	void compileElseIf();
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

