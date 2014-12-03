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
	void addVariable(string name, boost::any value, SymbolTable& symbolTable);
	void updateVariable(string name, boost::any value, SymbolTable& symbolTable);
private:
	SymbolTable* globalSymbolTable;
	Action* currentAction;
	void executeAction(CompilerToken* compilerToken, SymbolTable& symbolTable);
	void executeAction(ReturnValueCompilerToken* compilerToken, SymbolTable& symbolTable);
	void executeAction(AssignCompilerToken* compilerToken, SymbolTable& symbolTable);
	boost::any executeAction(FunctionCompilerToken* compilerToken, SymbolTable& symbolTable, Action* fAction);
	void executeAction(VarCompilerToken* compilerToken, SymbolTable& symbolTable);
	boost::any executeInternalFunction(std::string name, FunctionCompilerToken* compilerToken, SymbolTable& symbolTable);
	bool executeAction(ConditionCompilerToken* compilerToken, SymbolTable& symbolTable);
	bool exNumber(boost::any left, boost::any right, TokenType op, std::stack<boost::any>& resultStack);
	bool exString(boost::any left, boost::any right, TokenType op, std::stack<boost::any>& resultStack);
	bool exBool(boost::any left, boost::any right, TokenType op, std::stack<boost::any>& resultStack);
	boost::any getReturnValue(ReturnValueCompilerToken*, SymbolTable& symbolTable);
	boost::any getVarValue(VarCompilerToken*, SymbolTable& symbolTable);
	void print(boost::any);
};

