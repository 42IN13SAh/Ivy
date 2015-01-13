#ifndef DIVIDEBYZEROEXCEPTION_H
#define DIVIDEBYZEROEXCEPTION_H

#include <string>
#include "BaseException.h"

class DivideByZeroException : public BaseException {
public:
	DivideByZeroException() : BaseException("Cannot divide by zero") {}
};

#endif