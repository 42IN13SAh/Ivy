#pragma once

class VirtualMachine;

class CompilerToken
{
public:
	CompilerToken();
	virtual ~CompilerToken();

	virtual CompilerToken* Get() { return this; }
};

