#include "ReturnCompilerToken.h"

ReturnCompilerToken::ReturnCompilerToken(boost::shared_ptr<ReturnValueCompilerToken> rvct)
{
	this->rvct = rvct;
}

ReturnCompilerToken::~ReturnCompilerToken()
{

}

boost::shared_ptr<ReturnValueCompilerToken> ReturnCompilerToken::getReturnValueCompilerToken()
{
	return rvct;
}