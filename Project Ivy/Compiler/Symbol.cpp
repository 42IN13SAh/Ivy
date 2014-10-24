#include "Symbol.h"

Symbol::Symbol(string name, boost::any value)
{
	this->name = name;
	this->value = value;
}

Symbol::Symbol(string name)
{
	this->name = name;
}

Symbol::~Symbol()
{
}

string Symbol::getName()
{
	return this->name;
}

void Symbol::setValue(boost::any value)
{
	this->value = value;
}