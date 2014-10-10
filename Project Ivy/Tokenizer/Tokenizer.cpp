#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <regex>
#include "Tokenizer.h"

Tokenizer::Tokenizer()
{
	syntaxManager.jsonToSyntaxMap();
}

Tokenizer::~Tokenizer()
{
}

void Tokenizer::tokenize(std::string *input, int size)
{
	int lineNumber = 0;
	int previousSyntaxId = -1;
	int level = 0;
	while (++lineNumber <= size)
	{
		int linePosition = 0;
		std::string unprocessedInput = trim(*input);
		while (unprocessedInput != "")
		{
			bool hasMatch = false;
			for (Syntax* syntax : syntaxManager.getFollowupVector(previousSyntaxId))
			{
				std::smatch result;
				if (std::regex_search(unprocessedInput, result, std::regex(syntax->getRegexPattern())))
				{
					Token* t =  new Token(syntax->getID(), lineNumber, linePosition, level, result[0], syntax->getTokenType(), nullptr);
					tokenList.push_back(t);
					previousSyntaxId = syntax->getID();
					hasMatch = true;
					linePosition += result[0].length();
					unprocessedInput = trim(unprocessedInput.erase(0, result[0].length()));
					if (syntax->getShouldPush()){
						partnerStack.push(t);
						level++;
					}
					if (syntax->getPartners(syntaxManager.getSyntaxMap()).size() > 0){
						Token* stackToken = partnerStack.top();
						partnerStack.pop();
						for (Syntax* partner : syntax->getPartners(syntaxManager.getSyntaxMap())){
							if (stackToken->getSyntaxID() == partner->getID()){
								stackToken->setPartner(t);
								t->setPartner(stackToken);
							}
						}
						level--;
					}
					break;
				}
			}

			if (!hasMatch)
			{
			}
		}
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


int main(){
	Tokenizer tok;
	tok.tokenize(new std::string("func a;"), 1);
	return 0;
}