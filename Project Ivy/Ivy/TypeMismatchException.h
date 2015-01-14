#ifndef TYPEMISMATCHEXCEPTION_H
#define TYPEMISMATCHEXCEPTION_H

#include <string>
#include "BaseException.h"

class TypeMismatchException : public BaseException {
public:
	TypeMismatchException(const std::string& op, const std::string& type1, const std::string& type2) : BaseException("The given types did not match and could therefor not be handled properly\nTypes and operator: " + type1 + " " + op + " " + type2) {}
};

#endif