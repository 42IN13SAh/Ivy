#pragma once

#include <map>

#include "Syntax.h"

class SyntaxManager
{
public:
	SyntaxManager();
	virtual ~SyntaxManager();

	void jsonToSyntaxMap();

private:
	std::map<int, Syntax> *syntaxMap;
};

