#pragma once
#include <boost/any.hpp>

class CompilerToken
{
public:
	CompilerToken();
	~CompilerToken();
	bool execute();
	boost::any getResult();	

private:
	boost::any left;
	boost::any right;
	boost::any result;
};

