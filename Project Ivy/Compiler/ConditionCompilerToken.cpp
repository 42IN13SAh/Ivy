#include "ConditionCompilerToken.h"

ConditionCompilerToken::ConditionCompilerToken(ReturnValueCompilerToken* rvct) {
	this->rvct = rvct;
}

//ConditionCompilerToken::ConditionCompilerToken(std::vector<TokenType> cOpVector, std::vector<SubConditionCompilerToken*> subcons)
//{
//	/*this->cOperatorVector = cOpVector;
//	this->subcons = subcons;*/
//}

ConditionCompilerToken::~ConditionCompilerToken()
{
	delete rvct;
}
