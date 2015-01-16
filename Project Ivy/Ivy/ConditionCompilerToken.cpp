#include "ConditionCompilerToken.h"

ConditionCompilerToken::ConditionCompilerToken(boost::shared_ptr<ReturnValueCompilerToken> rvct) {
	this->rvct = rvct;
}

ConditionCompilerToken::~ConditionCompilerToken()
{
}
