#pragma once

#include <map>
#include <vector>

#include "Syntax.h"

class SyntaxManager
{
public:
	SyntaxManager();
	virtual ~SyntaxManager();

	void jsonToSyntaxMap();
	void fillFullSyntaxVector();
	std::vector<Syntax> getFollowupVector(int syntaxId);

private:
	std::map<int, Syntax> *syntaxMap;
	std::vector<Syntax> *fullSyntaxVector;
};

