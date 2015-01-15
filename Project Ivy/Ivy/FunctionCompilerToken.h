#pragma once
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"

class FunctionCompilerToken :
	public CompilerToken
{
public:
	FunctionCompilerToken(std::string);
	virtual ~FunctionCompilerToken();
	void setName(std::string);
	void addArgument(boost::shared_ptr<ReturnValueCompilerToken>);
	void addArgumentName(std::string);
	void setResult(boost::any);
	std::string getName();
	std::vector<boost::shared_ptr<ReturnValueCompilerToken>>& getArguments();
	std::vector<std::string> getArgumentNames();
	boost::any getResult();
private:
	std::string name;
	std::vector<boost::shared_ptr<ReturnValueCompilerToken>> arguments;
	std::vector<std::string> argumentNames;
	boost::any result;
};