#include "AssignCompilerToken.h"
#include "../Virtual Machine/VirtualMachine.h"
#include <iostream>

AssignCompilerToken::AssignCompilerToken(std::string name, ReturnValueCompilerToken* value)
{
	this->name = name;
	this->value = value;
}

AssignCompilerToken::~AssignCompilerToken()
{
	//delete value;
}

std::string AssignCompilerToken::getName() {
	return name;
}

ReturnValueCompilerToken* AssignCompilerToken::getReturnValue() {
	return value;
}