#pragma once
#include <boost/any.hpp>
#include "Action.h"
#include "SymbolTable.h"
#include <string>
#include <vector>

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
};

