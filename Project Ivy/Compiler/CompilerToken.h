#pragma once
#include <boost/any.hpp>

class VirtualMachine;

class CompilerToken
{
public:
	CompilerToken();
	~CompilerToken();
	virtual bool execute(VirtualMachine *vm);
};

