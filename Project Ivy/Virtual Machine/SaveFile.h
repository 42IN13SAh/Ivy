#pragma once
#include "IInternalFunction.h" 

class SaveFile : public IInternalFunction
{
public:
	~SaveFile();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};

