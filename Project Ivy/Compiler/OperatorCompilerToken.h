#pragma once
#include "CompilerToken.h"

class OperatorCompilerToken :
	public CompilerToken
{
public:
	OperatorCompilerToken();
	virtual ~OperatorCompilerToken();
	bool execute(VirtualMachine *vm);

	enum OperatorType { ADD, SUBSTRACT, MODULO, MULTIPLY, DIVIDE };

	void setOperatorType(OperatorType operatorType);

private:
	OperatorType operatorType;

	void performOperation(boost::any leftValue, boost::any rightValue);
};

