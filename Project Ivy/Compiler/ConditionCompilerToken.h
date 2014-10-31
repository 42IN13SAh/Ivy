#pragma once
#include <vector>
#include "CompilerToken.h"
#include "SubConditionCompilerToken.h"

enum ConditionOperator {AND, OR};

class ConditionCompilerToken : public CompilerToken
{
public:
	ConditionCompilerToken();
	~ConditionCompilerToken();
private:
	ConditionOperator cOperator;
	std::vector<SubConditionCompilerToken*> subcons;
};

