#include "SubConditionCompilerToken.h"


SubConditionCompilerToken::SubConditionCompilerToken()
{
}

SubConditionCompilerToken::~SubConditionCompilerToken()
{
	//delete left;
	//delete right;
}

void SubConditionCompilerToken::setLeft(ReturnValueCompilerToken* rv) {
	this->left = rv;
}

void SubConditionCompilerToken::setRight(ReturnValueCompilerToken* rv) {
	this->right = rv;
}

void SubConditionCompilerToken::setOperator(TokenType sco) {
	this->scOperator = sco;
}
