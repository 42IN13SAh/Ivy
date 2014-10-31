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

class VirtualMachine
{
public:
	VirtualMachine();
	~VirtualMachine();

	void run(Action *firstAction);
	void addVariable(string name, boost::any value);
	void updateVariable(string name, boost::any value);

private:
	vector<SymbolTable> symbolTables;
	SymbolTable currentSymbolTable;

	Action* executeAction(AssignCompilerToken compilerToken);
	Action* executeAction(ConditionCompilerToken compilerToken);
	Action* executeAction(FunctionCompilerToken compilerToken);
	Action* executeAction(ReturnValueCompilerToken compilerToken);
	Action* executeAction(SubConditionCompilerToken compilerToken);
};

