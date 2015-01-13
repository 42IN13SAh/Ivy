#ifndef UNEXPECTEDOPERATOREXCEPTION_H
#define UNEXPECTEDOPERATOREXCEPTION_H

#include <string>
#include "BaseException.h"

class UnexpectedOperatorException : public BaseException {
public:
	UnexpectedOperatorException(const std::string& op, const std::string& type) : BaseException("Unexpected operator, cannot process: " + type + " with operator " + op) {}
	UnexpectedOperatorException(const std::string& op, const std::string& type1, const std::string& type2) : BaseException("Unexpected operator, cannot process: " + type1 + " and " + type2 + " with operator " + op) {}
};

#endif