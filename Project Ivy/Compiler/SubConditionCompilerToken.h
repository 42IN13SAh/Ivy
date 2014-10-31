#pragma once
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"

enum SubConditionOperator {GreaterThen, SmallerThen, SmallerEquals, GreaterEquals, Is, Not};

class SubConditionCompilerToken : public CompilerToken
{
public:
	SubConditionCompilerToken();
	~SubConditionCompilerToken();
private:
	SubConditionOperator scOperator;
	ReturnValueCompilerToken* left;
	ReturnValueCompilerToken* right;
};

