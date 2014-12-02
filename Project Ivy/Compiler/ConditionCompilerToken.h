#pragma once
#include <vector>
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"
//#include "SubConditionCompilerToken.h"

class ConditionCompilerToken : public CompilerToken
{
public:
	//ConditionCompilerToken(std::vector<TokenType>, std::vector<SubConditionCompilerToken*>);
	ConditionCompilerToken(ReturnValueCompilerToken*);
	virtual ~ConditionCompilerToken();

	enum ConditionOperator { AND, OR };

	//virtual ConditionCompilerToken* Get() { return this; }
	ReturnValueCompilerToken* getReturnValueCompilerToken() { return rvct; }

private:
	/*std::vector<TokenType> cOperatorVector;
	std::vector<SubConditionCompilerToken*> subcons;*/
	ReturnValueCompilerToken* rvct;
};

