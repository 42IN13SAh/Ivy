#include "Symbol.h"
Symbol::Symbol(std::string name, boost::any value)
{
	this->name = name;
	this->value = value;
}

Symbol::Symbol(std::string name)
{
	this->name = name;
}

Symbol::~Symbol()
{
}

std::string Symbol::getName()
{
	return this->name;
}

void Symbol::setValue(boost::any value)
{
	this->value = value;
}

boost::any Symbol::getValue()
{
	return this->value;
}