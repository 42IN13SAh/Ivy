#pragma once
#include <string>
#include <boost\any.hpp>
class Symbol
{
public:
	Symbol(std::string name, boost::any value);
	Symbol(std::string name);
	~Symbol();
	std::string getName();
	boost::any getValue();
	void setValue(boost::any value);
private:
	std::string name;
	boost::any value;
};

