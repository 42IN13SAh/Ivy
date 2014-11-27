#include "ConsoleInput.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("consoleInput", ConsoleInput);

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
