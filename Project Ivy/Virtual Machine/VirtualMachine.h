#pragma once
#include <boost/any.hpp>
#include "../Compiler/Action.h"
#include "../Compiler/SymbolTable.h"
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <stack>
#include "../Tokenizer/TokenType.h"
#include "InternalFunctionFactory.h"

class AssignCompilerToken;
class ConditionCompilerToken;
class FunctionCompilerToken;
class ReturnValueCompilerToken;
class SubConditionCompilerToken;
class VarCompilerToken;

class VirtualMachine
{
public:
	VirtualMachine(SymbolTable* symbolTable);
	VirtualMachine();
	~VirtualMachine();
	void run(Action *firstAction);
	void addVariable(string name, boost::any value);
	void updateVariable(string name, boost::any value);
private:
	SymbolTable* currentSymbolTable;
	SymbolTable* globalSymbolTable;
	Action* currentAction;
	void executeAction(CompilerToken*);
	void executeAction(ReturnValueCompilerToken* compilerToken);
	void executeAction(AssignCompilerToken* compilerToken);
	void executeAction(FunctionCompilerToken* compilerToken, Action* lastAction);
	void executeAction(VarCompilerToken* compilerToken);
	void executeAction(ConditionCompilerToken* compilerToken);
	bool exNumber(boost::any left, boost::any right, TokenType op, std::stack<boost::any>& resultStack);
	bool exString(boost::any left, boost::any right, TokenType op, std::stack<boost::any>& resultStack);
	bool exBool(boost::any left, boost::any right, TokenType op, std::stack<boost::any>& resultStack);
	boost::any getReturnValue(ReturnValueCompilerToken*);
	boost::any getVarValue(VarCompilerToken*);
	boost::any getFunctionValue(FunctionCompilerToken*, Action* lastAction);
	void print(boost::any);
};

