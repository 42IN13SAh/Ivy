#ifndef SYMBOLALREADYEXISTSEXCEPTION_H
#define SYMBOLALREADYEXISTSEXCEPTION_H

#include <string>
#include "BaseException.h"

class SymbolAlreadyExistsException : public BaseException
{
public:
	SymbolAlreadyExistsException(int lnr, int lps, const std::string& symbol, const std::string& type) : BaseException(lnr, lps) {
		exceptionMessage = type + " '" + symbol + "' is already defined on line "+ std::to_string(lnr) + " and position " + std::to_string(lps);
	}
	virtual ~SymbolAlreadyExistsException() {}
};


#endif