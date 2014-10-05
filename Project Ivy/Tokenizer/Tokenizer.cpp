#include "Tokenizer.h"

Tokenizer::Tokenizer()
{
	partnerStack = new std::stack<Token>();
	tokenList = new std::list<Token>();
	syntaxManager = new SyntaxManager();
}

Tokenizer::~Tokenizer()
{
	delete partnerStack;
	delete tokenList;
	delete syntaxManager;
}

void Tokenizer::tokenize(std::string *input, int size)
{
	int lineNumber = 0;

	while (lineNumber++ <= size)
	{
		int linePosition = 0;

		// To-do: trimming and all the other stuff...
		// Check the boost library for trimming
	}
}

