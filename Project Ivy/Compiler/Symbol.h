#pragma once
#include <string>
#include <boost/any.hpp>

using namespace std;

class Symbol
{
public:
	Symbol();
	~Symbol();

private:
	string name;
	boost::any value;
};

