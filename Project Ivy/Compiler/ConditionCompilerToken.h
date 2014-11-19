#pragma once
#include <vector>
#include "CompilerToken.h"
#include "SubConditionCompilerToken.h"

class ConditionCompilerToken : public CompilerToken
{
public:
	ConditionCompilerToken(std::vector<TokenType>, std::vector<SubConditionCompilerToken*>);
	virtual ~ConditionCompilerToken();

	enum ConditionOperator { AND, OR };

	virtual ConditionCompilerToken* Get() { return this; }

private:
	std::vector<TokenType> cOperatorVector;
	std::vector<SubConditionCompilerToken*> subcons;
};

