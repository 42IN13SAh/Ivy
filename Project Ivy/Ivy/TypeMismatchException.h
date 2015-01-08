#ifndef TYPEMISMATCHEXCEPTION_H
#define TYPEMISMATCHEXCEPTION_H

#include <string>
#include "BaseException.h"

class TypeMismatchException : public BaseException {
public:
	TypeMismatchException() : BaseException("The given types did not match and could therefor not be handled properly") {}
};

#endif