#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <regex>
#include <fstream>
#include <chrono>
#include <boost\algorithm\string\trim.hpp>
#include "Tokenizer.h"
#include "PartnerNotFoundException.h"
#include "ReservedKeywordException.h"

Tokenizer::Tokenizer()
{
	syntaxManager.jsonToSyntaxMap();
}

Tokenizer::~Tokenizer()
{
	for each(Token* token in tokenList){
		delete token;
	}
}


std::list<Token*> Tokenizer::getTokenList()
{
	return tokenList;
}

const std::vector<BadSyntaxException>& Tokenizer::getErrorList() {
	return errorList;
}

void Tokenizer::tokenize(std::string* input, int size)
{
	int lineNumber = 0;
	int syntaxId = -1;
	int level = 0;

	while (++lineNumber <= size){
		int linePosition = 1;
		const char* unprocessedInput = trim(input->c_str(), linePosition);
		while (*unprocessedInput != '\0'){
			bool hasMatch = false;
			for (Syntax* syntax : syntaxManager.getFollowupVector(syntaxId)){
				boost::cmatch result;
				if (boost::regex_search(unprocessedInput, result, syntax->getRegexPattern(), boost::match_continuous)){
					hasMatch = true;
					Token* token = new Token(syntax->getID(), lineNumber, linePosition, level, result[0], syntax->getTokenType(), syntax->getParentType(), nullptr);
					if (token->getTokenType() == TokenType::Name){
						if (syntaxManager.hasKeyWord(token->getDescription())){
							errorList.push_back(ReservedKeywordException(token->getDescription(), lineNumber, linePosition));
							linePosition += result[0].length();
							unprocessedInput += result[0].length();
							break;
							// throw ReservedKeywordException(token->getDescription(), lineNumber, linePosition);
						}
					}
					tokenList.push_back(token);
					tokenPartnerCheck(syntax, token, level, lineNumber, linePosition);
					linePosition += result[0].length();
					unprocessedInput += result[0].length();
					unprocessedInput = trim(unprocessedInput, linePosition);
					syntaxId = syntax->getID();
					break;
				}
			}
			if (!hasMatch){
				errorList.push_back(BadSyntaxException(lineNumber, linePosition));
				unprocessedInput++;
				linePosition++;
				//syntaxId = -1;
				//throw BadSyntaxException(lineNumber, linePosition);
			}
		}
		input++;
	}
}

void Tokenizer::tokenPartnerCheck(Syntax* syntax, Token* token, int& level, int& linenumber, int& lineposition)
{
	if (syntax->getShouldPush()){
		partnerStack.push(token);
		if (token->getTokenType() != TokenType::IfStatement)
			level++;
	}
	if (syntax->getPartners().size() > 0){
		if (partnerStack.size() == 0){
			errorList.push_back(PartnerNotFoundException(token->getDescription(), linenumber, lineposition));
			// throw PartnerNotFoundException(token->getDescription(), linenumber, lineposition);
			return;
		}
		Token* stackToken = partnerStack.top();
		partnerStack.pop();
		if (token->getTokenType() == TokenType::ClosingBracket){
			while (stackToken->getTokenType() == TokenType::IfStatement){
				stackToken = partnerStack.top();
				partnerStack.pop();
			}
		}
		for (Syntax* partner : syntax->getPartners()){
			if (stackToken->getSyntaxID() == partner->getID()){
				stackToken->setPartner(token);
				token->setPartner(stackToken);
				break;
			}
		}
		if (token->getTokenType() != TokenType::ElseStatement){
			level--;
		}
	}
}

const char* Tokenizer::trim(const char* str, int& lineposition)
{
	const char* end;
	while (*str == ' ' || *str == '\t'){
		if (*str == '\t'){
			lineposition += 4;
		}
		else{
			lineposition++;
		}
		str++;
	}
	if (*str == 0){
		return str;
	}
	end = str + strlen(str);
	while (end > str && *end == ' ' || *end == '\t'){
		if (*str == '\t'){
			lineposition += 4;
		}
		else{
			lineposition++;
		}
		end--;
	}
	return str;
}
