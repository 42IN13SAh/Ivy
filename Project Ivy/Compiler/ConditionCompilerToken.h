#pragma once
#include <vector>
#include "CompilerToken.h"
#include "SubConditionCompilerToken.h"

using namespace std;

enum ConditionOperator {AND, OR};

class ConditionCompilerToken : public CompilerToken
{
public:
	ConditionCompilerToken();
	~ConditionCompilerToken();
private:
	ConditionOperator cOperator;
	vector<SubConditionCompilerToken*> subcons;
};

