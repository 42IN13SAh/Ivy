#pragma once
#include "Tokenizer.h"
class SyntaxManager
{
public:
	SyntaxManager();
	virtual ~SyntaxManager();

	void init();

private:
	Tokenizer* tokenizer;
};

