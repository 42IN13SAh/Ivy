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

class AssignCompilerToken;
class ConditionCompilerToken;
class FunctionCompilerToken;
class ReturnValueCompilerToken;
class SubConditionCompilerToken;
class VarCompilerToken;

class VirtualMachine
{
public:
	VirtualMachine(SymbolTable* symbolTable); //Temporary constructor, not the right one yet!!!
	VirtualMachine();
	~VirtualMachine();

	void run(Action *firstAction);
	void addVariable(string name, boost::any value);
	void updateVariable(string name, boost::any value);

private:
	//vector<SymbolTable> symbolTables;
	SymbolTable* currentSymbolTable;
	Action* currentAction;

	void executeAction(CompilerToken*);
	void executeAction(ReturnValueCompilerToken* compilerToken);
	void executeAction(AssignCompilerToken* compilerToken);
	void executeAction(FunctionCompilerToken* compilerToken);
	void executeAction(VarCompilerToken* compilerToken);
	void executeAction(ConditionCompilerToken* compilerToken);
	//void executeAction(SubConditionCompilerToken* compilerToken);
	bool exNumber(boost::any left, boost::any right, TokenType op, std::stack<boost::any>& resultStack);
	bool exString(boost::any left, boost::any right, TokenType op, std::stack<boost::any>& resultStack);
	bool exBool(boost::any left, boost::any right, TokenType op, std::stack<boost::any>& resultStack);
	boost::any getReturnValue(ReturnValueCompilerToken*);
	boost::any getVarValue(VarCompilerToken*);
	boost::any getFunctionValue(FunctionCompilerToken*);

	void print(boost::any);
};

