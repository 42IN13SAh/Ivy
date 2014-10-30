#pragma once
#include "CompilerToken.h"

class MathOperatorCompilerToken :
	public CompilerToken
{
public:
	MathOperatorCompilerToken();
	virtual ~MathOperatorCompilerToken();
	bool execute(VirtualMachine *vm);

	enum OperatorType { ADD, SUBSTRACT, MODULO, MULTIPLY, DIVIDE };

	void setOperatorType(OperatorType operatorType);

private:
	OperatorType operatorType;

	void performOperation(boost::any leftValue, boost::any rightValue);
};

