#include "ReturnValueCompilerToken.h"


ReturnValueCompilerToken::ReturnValueCompilerToken()
{
	this->openParenthisCounter = 0;
}

ReturnValueCompilerToken::~ReturnValueCompilerToken()
{
}

void ReturnValueCompilerToken::addValueToVector(boost::any value)
{
	rpnVector.push(value);
}

bool ReturnValueCompilerToken::isEmpty()
{
	return operatorStack.empty();
}

void ReturnValueCompilerToken::pushOperatorToStack(TokenType op)
{
	if (op == TokenType::OpenParenthesis){
		openParenthisCounter++;
	}
	operatorStack.push(op);
}

TokenType ReturnValueCompilerToken::peekOperatorStack()
{
	if (!operatorStack.empty()) {
		return operatorStack.top();
	}

	return TokenType::Null;
}

bool ReturnValueCompilerToken::hasOpenParenthisOnStack()
{
	if (openParenthisCounter > 0){
		return true;
	}
	return false;
}

void ReturnValueCompilerToken::popOperatorStack()
{
	if (!operatorStack.empty()){
		if (operatorStack.top() == TokenType::OpenParenthesis){
			openParenthisCounter--;
		}
		operatorStack.pop();
	}
}

void ReturnValueCompilerToken::completeRPNVector()
{
	while (!operatorStack.empty()) {
		addValueToVector(operatorStack.top());
		operatorStack.pop();
	}
}

std::queue<boost::any>& ReturnValueCompilerToken::getRPN()
{
	return rpnVector;
}