#include "ConditionCompilerToken.h"

ConditionCompilerToken::ConditionCompilerToken(ReturnValueCompilerToken* rvct) {
	this->rvct = rvct;
}

ConditionCompilerToken::~ConditionCompilerToken()
{
	delete rvct;
}
