#include "OperatorCompilerToken.h"
#include "VirtualMachine.h"

OperatorCompilerToken::OperatorCompilerToken()
{
}


OperatorCompilerToken::~OperatorCompilerToken()
{
}

void OperatorCompilerToken::setOperatorType(OperatorType operatorType)
{
	this->operatorType = operatorType;
}

bool OperatorCompilerToken::execute(VirtualMachine *vm)
{
	boost::any leftValue;
	boost::any rightValue;

	if (left.type() == typeid(CompilerToken))
	{
		CompilerToken leftCompilerToken = boost::any_cast<CompilerToken>(left);
		leftCompilerToken.execute(vm);
		leftValue = leftCompilerToken.getResult();				
	}
	else
	{
		leftValue = left;
	}

	if (right.type() == typeid(CompilerToken))
	{
		CompilerToken rightCompilerToken = boost::any_cast<CompilerToken>(right);
		rightCompilerToken.execute(vm);
		rightValue = rightCompilerToken.getResult();
	}
	else
	{
		rightValue = left;
	}

	//Add may be used by strings and ints, the rest only by ints
	if (operatorType == ADD && leftValue.type() == typeid(string) && rightValue.type() == typeid(string))
	{
		performOperation(leftValue, rightValue);
	}
	else if (leftValue.type() == typeid(int) && rightValue.type() == typeid(int))
	{
		performOperation(leftValue, rightValue);
	}
	else
	{
		//TODO: better exception handling
		throw new exception; //the left and rightvalue must be ints or strings and both need to be the same type. If this point is reached then that is NOT the case.
	}

	return true;
}

void OperatorCompilerToken::performOperation(boost::any leftValue, boost::any rightValue)
{
	switch (operatorType)
	{
		case ADD:
			result = boost::any_cast<int>(leftValue) + boost::any_cast<int>(rightValue);
			break;

		case SUBSTRACT:
			result = boost::any_cast<int>(leftValue) - boost::any_cast<int>(rightValue);
			break;

		case MULTIPLY:
			result = boost::any_cast<int>(leftValue) * boost::any_cast<int>(rightValue);
			break;

		case MODULO:
			result = boost::any_cast<int>(leftValue) % boost::any_cast<int>(rightValue);
			break;

		case DIVIDE:
			result = boost::any_cast<int>(leftValue) / boost::any_cast<int>(rightValue);
			break;
	}
}