#pragma once
#include <vector>
#include <boost/shared_ptr.hpp>
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"

class ConditionCompilerToken : public CompilerToken
{
public:
	ConditionCompilerToken(boost::shared_ptr<ReturnValueCompilerToken> rvct);
	virtual ~ConditionCompilerToken();
	boost::shared_ptr<ReturnValueCompilerToken> getReturnValueCompilerToken() { return rvct; }

private:
	boost::shared_ptr<ReturnValueCompilerToken> rvct;
};

