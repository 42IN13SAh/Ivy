#include "ReturnValueCompilerToken.h"


ReturnValueCompilerToken::ReturnValueCompilerToken()
{
}


ReturnValueCompilerToken::~ReturnValueCompilerToken()
{
}

void ReturnValueCompilerToken::setSingleResult(boost::any r) { result = r; }
boost::any ReturnValueCompilerToken::getSingleResult() { return result; }