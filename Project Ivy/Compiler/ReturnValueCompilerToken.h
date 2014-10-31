#pragma once
#include <vector>
#include "CompilerToken.h"
#include "boost/any.hpp"

using namespace std;

enum MathOperator { ADD, SUBSTRACT, MODULO, MULTIPLY, DIVIDE };

class ReturnValueCompilerToken : public CompilerToken
{
public:
	ReturnValueCompilerToken();
	~ReturnValueCompilerToken();

	void setSingleResult(boost::any);
	boost::any getSingleResult();

private:
	//vector<MathOperatorCompilerToken*> nestedResults;
	boost::any result;
};

