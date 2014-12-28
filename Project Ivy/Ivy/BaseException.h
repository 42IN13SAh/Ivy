#pragma once
#include <exception>

class BaseException : public std::exception
{
public:
	BaseException(int lnr, int lps) : lineNr(lnr), linePos(lps) { }
	BaseException(int lnr, int lps, const std::string& msg) : lineNr(lnr), linePos(lps), exceptionMessage(msg) { }
	virtual ~BaseException(){}

	virtual int getLineNumber() { return lineNr; }
	virtual int getLinePosition() { return linePos; }

	virtual const char* what() const throw(){ return exceptionMessage.c_str(); }

private:
	int lineNr;
	int linePos;
protected:
	std::string exceptionMessage;
};

