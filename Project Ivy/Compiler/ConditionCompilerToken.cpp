#include "ConditionCompilerToken.h"


ConditionCompilerToken::ConditionCompilerToken(std::vector<TokenType> cOpVector, std::vector<SubConditionCompilerToken*> subcons)
{
	this->cOperatorVector = cOpVector;
	this->subcons = subcons;
}

ConditionCompilerToken::~ConditionCompilerToken()
{
	for each(SubConditionCompilerToken* sc in subcons) {
		//delete sc;
	}
}
