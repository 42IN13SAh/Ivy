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
#include "SymbolAlreadyExistsException.h"
#include "UndefinedSymbolException.h"

class Compiler
{
public:
	Compiler(std::list<Token*>);
	~Compiler();
	void compile();
	Action* getFirstAction();
	SymbolTable* getSymbolTable();
	const std::vector<BaseException>& getErrorList();
	std::vector<std::string> getAllFunctionAndVariableNames();
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
	std::vector<Action*> actions;

	void compileFunction();
	void addFunctionSignature();
	void compileCodeBlock();
	void compileStatement();
	void compileWhile();
	void compileIf();
	void compileElseIf();
	Action* compileElse();
	boost::shared_ptr<ReturnValueCompilerToken> compileReturnValue();
	boost::shared_ptr<ConditionCompilerToken> compileCondition();
	boost::shared_ptr<FunctionCompilerToken> compileFunctionCall();
	Action* compileStatementVar(Action*);
	Action* compileStatementName(Action*);
	void compileReturnValueName(boost::shared_ptr<ReturnValueCompilerToken>);
	void compileReturnValueIncreaseDecrease(boost::shared_ptr<ReturnValueCompilerToken>);
	void compileReturnValueMath(boost::shared_ptr<ReturnValueCompilerToken>);
	Token* getCurrentToken();
	Token* getNextToken();
	Token* peekNextToken();
	void resetTokenIter();
	void addInternalFunctions();
	Action* createAction();
	DoNothingAction* createDoNothing();
};

