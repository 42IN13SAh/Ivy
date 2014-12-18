#ifndef UNDEFINEDSYMBOLEXCEPTION_H
#define UNDEFINEDSYMBOLEXCEPTION_H

#include <string>
#include "BaseException.h"

class UndefinedSymbolException : public BaseException
{
public:
	UndefinedSymbolException(int lnr, int lps, std::string symbol, std::string type) : BaseException(lnr, lps) {
		exceptionMessage = type + " '" + symbol + "' is undefined on line " + std::to_string(lnr) + " and position " + std::to_string(lps);
	}
	virtual ~UndefinedSymbolException() {}
};


#endif