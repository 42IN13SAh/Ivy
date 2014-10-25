#pragma once
#include <boost/any.hpp>

class VirtualMachine;

class CompilerToken
{
public:
	CompilerToken();
	~CompilerToken();
	virtual bool execute(VirtualMachine *vm);
	boost::any getResult();	

protected:
	boost::any left;
	boost::any right;
	boost::any result;
};

