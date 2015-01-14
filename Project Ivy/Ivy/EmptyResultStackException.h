#ifndef EMPTYRESULTSTACKEXCEPTION_H
#define EMPTYRESULTSTACKEXCEPTION_H

#include "BaseException.h"

class EmptyResultStackException : public BaseException {
public:
	EmptyResultStackException() : BaseException("Unexpected empty result stack") {}
};

#endif