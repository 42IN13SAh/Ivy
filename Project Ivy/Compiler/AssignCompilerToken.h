#pragma once
#include <string>
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"

using namespace std;

class AssignCompilerToken :
	public CompilerToken
{
public:
	AssignCompilerToken();
	virtual ~AssignCompilerToken();
	bool execute(VirtualMachine *vm);

private:
	string name;
	ReturnValueCompilerToken* value;
};

