#ifndef VARIABLENOTFOUNDEXCEPTION_H
#define VARIABLENOTFOUNDEXCEPTION_H

#include <string>
#include "BaseException.h"

class VariableNotFoundException : public BaseException {
public:
	VariableNotFoundException(const std::string& var) : BaseException("Unable to find variable: " + var) {}
};

#endif