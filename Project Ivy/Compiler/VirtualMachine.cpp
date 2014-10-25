#include "VirtualMachine.h"


VirtualMachine::VirtualMachine()
{
}


VirtualMachine::~VirtualMachine()
{
}

void VirtualMachine::run(Action *firstAction)
{
	Action *action = firstAction;

	while (action != nullptr)
	{
		try
		{
			action = action->getNextAction();
			//TODO: set the current scope and symboltable
		}
		catch (exception e)
		{
			//TODO: runtime error handling
		}
	}
}

void VirtualMachine::addVariable(string name, boost::any value)
{
	currentSymbolTable.addSymbolToTable(name, value);
}

void VirtualMachine::updateVariable(string name, boost::any value)
{
	currentSymbolTable.updateExistingSymbol(name, value);
}