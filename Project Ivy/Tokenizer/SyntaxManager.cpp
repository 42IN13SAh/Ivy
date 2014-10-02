#include "SyntaxManager.h"
#include <iostream>

int main()
{
	SyntaxManager* syntaxManager = new SyntaxManager();
	return 0;
}

void SyntaxManager::init()
{
	Tokenizer* tokenizer = new Tokenizer(); 
}

SyntaxManager::SyntaxManager()
{
	this->init();
}


SyntaxManager::~SyntaxManager()
{
	
}
