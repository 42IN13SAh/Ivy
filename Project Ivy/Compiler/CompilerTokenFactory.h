#pragma once

#include <map>

#include "CompilerToken.h"

using namespace std;

class CompilerTokenFactory
{
public:
	CompilerTokenFactory();
	~CompilerTokenFactory();

private:
	map<string, CompilerToken> map;
};

