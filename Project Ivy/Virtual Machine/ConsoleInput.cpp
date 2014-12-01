#include "ConsoleInput.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("consoleInput", ConsoleInput, 0);

void ConsoleInput::Execute(std::vector<boost::any> arglist)
{

}

boost::any ConsoleInput::GetResult()
{
	return Result;
}

ConsoleInput::~ConsoleInput()
{
}
