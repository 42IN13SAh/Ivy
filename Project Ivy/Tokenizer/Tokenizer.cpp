#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

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
	int previousSyntaxId = -1;

	while (lineNumber++ <= size)
	{
		int linePosition = 0;

		std::string unprocessedInput = trim(*input);

		while (unprocessedInput != "")
		{
			bool hasMatch = false;

			for (Syntax &syntax : syntaxManager->getFollowupVector(previousSyntaxId))
			{
				// Check with regex and create a token.

				// Create token
				// Set previous syntax id
				// Set match status
				// Trim start of string
				// Update local variables
				// Break loop
			}

			if (!hasMatch)
			{
				// Crash burn and die.
			}
		}

		// Feed next line
		input++;
	}
}

// Temporaty trimming code. Will be replaced by the Boost library later when the project is merged.
// trim from start
std::string &Tokenizer::ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
std::string &Tokenizer::rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
std::string &Tokenizer::trim(std::string &s) {
	return ltrim(rtrim(s));
}

