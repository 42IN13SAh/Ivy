#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include "TokenType.h"
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"

class AssignCompilerToken :
	public CompilerToken
{
public:
	AssignCompilerToken(std::string, boost::shared_ptr<ReturnValueCompilerToken>, TokenType::TokenType tokenType);
	virtual ~AssignCompilerToken();
	std::string getName();
	boost::shared_ptr<ReturnValueCompilerToken> getReturnValue();
	TokenType::TokenType getAssignOp();
private:
	std::string name;
	boost::shared_ptr<ReturnValueCompilerToken> value;
	TokenType::TokenType assignOp;
};