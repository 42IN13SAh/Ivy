#pragma once
#include <boost/any.hpp>
#include "../Compiler/Action.h"
#include "../Compiler/SymbolTable.h"
#include <string>
#include <vector>
#include <iostream>

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
	void executeAction(AssignCompilerToken* compilerToken);
	void executeAction(ConditionCompilerToken* compilerToken);
	void executeAction(FunctionCompilerToken* compilerToken);
	void executeAction(SubConditionCompilerToken* compilerToken);
	void executeAction(VarCompilerToken* compilerToken);

	boost::any executeReturnValue(ReturnValueCompilerToken*);

	void print(boost::any);
};

