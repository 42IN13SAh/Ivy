#pragma once
#include <string>
#include <boost/any.hpp>

using namespace std;

class Symbol
{
public:
	Symbol(string name, boost::any value);
	Symbol(string name);
	~Symbol();

	string getName();
	void setValue(boost::any value);

private:
	string name;
	boost::any value;
};

