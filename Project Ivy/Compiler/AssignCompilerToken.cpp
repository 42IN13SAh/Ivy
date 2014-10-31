#include "AssignCompilerToken.h"
#include "../Virtual Machine/VirtualMachine.h"

AssignCompilerToken::AssignCompilerToken(std::string name, ReturnValueCompilerToken* value)
{
	this->name = name;
	this->value = value;
}

AssignCompilerToken::~AssignCompilerToken()
{
}

std::string AssignCompilerToken::getName() {
	return name;
}

ReturnValueCompilerToken* AssignCompilerToken::getReturnValue() {
	return value;
}
