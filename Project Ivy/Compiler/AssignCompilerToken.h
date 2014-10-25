#pragma once
#include "CompilerToken.h"

class AssignCompilerToken :
	public CompilerToken
{
public:
	AssignCompilerToken();
	virtual ~AssignCompilerToken();
	bool execute(VirtualMachine *vm);
};

