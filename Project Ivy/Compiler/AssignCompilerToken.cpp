#include "AssignCompilerToken.h"
#include "VirtualMachine.h"

AssignCompilerToken::AssignCompilerToken()
{
}


AssignCompilerToken::~AssignCompilerToken()
{
}

bool AssignCompilerToken::execute(VirtualMachine *vm)
{
	//the left hand of an assign is always a variable name
	std::string name = boost::any_cast<std::string>(left);

	if (right.type() == typeid(CompilerToken))
	{
		CompilerToken rightCompilerToken = boost::any_cast<CompilerToken>(right);
		rightCompilerToken.execute(vm);
		vm->updateVariable(name, rightCompilerToken.getResult());
	}
	else
	{
		vm->updateVariable(name, right);
	}

	return true;
}