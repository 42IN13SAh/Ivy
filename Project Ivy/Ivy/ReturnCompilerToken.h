#pragma once
#include <boost/shared_ptr.hpp>
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"
class ReturnCompilerToken :
	public CompilerToken
{
public:
	ReturnCompilerToken(boost::shared_ptr<ReturnValueCompilerToken>);
	virtual ~ReturnCompilerToken();
	boost::shared_ptr<ReturnValueCompilerToken> getReturnValueCompilerToken();
private:
	boost::shared_ptr<ReturnValueCompilerToken> rvct;
};

