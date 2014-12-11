#include "ReturnCompilerToken.h"

ReturnCompilerToken::ReturnCompilerToken(ReturnValueCompilerToken* rvct)
{
	this->rvct = rvct;
}

ReturnCompilerToken::~ReturnCompilerToken()
{
	delete rvct;
}

ReturnValueCompilerToken* ReturnCompilerToken::getReturnValueCompilerToken()
{
	return rvct;
}