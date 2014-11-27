#include "ReturnValueCompilerToken.h"


ReturnValueCompilerToken::ReturnValueCompilerToken()
{
}

ReturnValueCompilerToken::~ReturnValueCompilerToken()
{
}

void ReturnValueCompilerToken::addValueToVector(boost::any value) { 
	rpnVector.push(value);
}

bool ReturnValueCompilerToken::isEmpty()
{
	return operatorStack.empty();
}

void ReturnValueCompilerToken::pushOperatorToStack(TokenType op) { 
	operatorStack.push(op);
}

TokenType ReturnValueCompilerToken::peekOperatorStack() {
	if (!operatorStack.empty()) {
		return operatorStack.top();
	}

	return TokenType::Null;
}

void ReturnValueCompilerToken::popOperatorStack() {
	if(!operatorStack.empty()) operatorStack.pop();
}

void ReturnValueCompilerToken::completeRPNVector() {
	while (!operatorStack.empty()) {
		addValueToVector(operatorStack.top());
		operatorStack.pop();
	}
}

std::queue<boost::any>& ReturnValueCompilerToken::getRPN() {
	return rpnVector;
}