#pragma once
#include <boost/any.hpp>
#include "../Compiler/Action.h"
#include "../Compiler/SymbolTable.h"
#include <string>
#include <vector>

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
	vector<SymbolTable> symbolTables;
	SymbolTable* currentSymbolTable;

	Action* executeAction(Action* action, AssignCompilerToken* compilerToken);
	Action* executeAction(Action* action, ConditionCompilerToken* compilerToken);
	Action* executeAction(Action* action, FunctionCompilerToken* compilerToken);
	Action* executeAction(Action* action, ReturnValueCompilerToken* compilerToken);
	Action* executeAction(Action* action, SubConditionCompilerToken* compilerToken);
	Action* executeAction(Action* action, VarCompilerToken* compilerToken);
};

