#include "RandomWithPara.h"
#include "Time.h"
RandomWithPara::~RandomWithPara()
{
}

void RandomWithPara::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	if (a){
		Result = (double) (rand() % (int)a);
	}
	else{
		Result = (double) rand();
	}
}

boost::any RandomWithPara::GetResult()
{
	return Result;
}

