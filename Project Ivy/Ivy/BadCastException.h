#ifndef BADCASTEXCEPTION_H
#define BADCASTEXCEPTION_H

#include <string>
#include "BaseException.h"

class BadCastException : public BaseException {
public:
	BadCastException(const std::string& expType, const std::string& recType) : BaseException("Invalid type conversion. Expected type: "+expType+", Received type: " +recType) {}
};

#endif