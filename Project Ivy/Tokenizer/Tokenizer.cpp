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


std::list<Token*> Tokenizer::getTokenList()
{
	return tokenList;
}

void Tokenizer::tokenize(std::string *input, int size)
{
	int lineNumber = 0;
	int syntaxId = -1;
	int level = 0;
	while (++lineNumber <= size){
		int linePosition = 0;
		std::string unprocessedInput = trim(*input);
		while (unprocessedInput != ""){
			bool hasMatch = false;
			for (Syntax* syntax : syntaxManager.getFollowupVector(syntaxId)){
				std::smatch result;
				if (std::regex_search(unprocessedInput, result, std::regex(syntax->getRegexPattern()))){
					hasMatch = true;
					Token* token = new Token(syntax->getID(), lineNumber, linePosition, level, result[0], syntax->getTokenType(), nullptr);
					checkIfTokenIsVariableNameOrFunctionName(token);
					tokenList.push_back(token);
					tokenPartnerCheck(syntax, token, level);
					linePosition += result[0].length();
					unprocessedInput = trim(unprocessedInput.erase(0, result[0].length()));
					syntaxId = syntax->getID();
					break;
				}
			}
			if (!hasMatch){
				//raise syntax error
			}
		}
		input++;
	}
}

void Tokenizer::checkIfTokenIsVariableNameOrFunctionName(Token* token)
{
	if (token->getTokenType() == FunctionName){
		functionNames.push_back(token->getDescription());
	}
	if (token->getTokenType() == VarName){
		variableNames.push_back(token->getDescription());
	}
}

void Tokenizer::tokenPartnerCheck(Syntax* syntax, Token* token, int level)
{
	if (syntax->getShouldPush()){
		partnerStack.push(token);
		level++;
	}
	if (syntax->getPartners(syntaxManager.getSyntaxMap()).size() > 0){
		Token* stackToken = partnerStack.top();
		partnerStack.pop();
		for (Syntax* partner : syntax->getPartners(syntaxManager.getSyntaxMap())){
			if (stackToken->getSyntaxID() == partner->getID()){
				stackToken->setPartner(token);
				token->setPartner(stackToken);
			}
		}
		level--;
	}
}
// Temporaty trimming code. Will be replaced by the Boost library
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
	tok.tokenize(new std::string("var x = 5;function x(); if(x = 3)"), 1);
	return 0;
}