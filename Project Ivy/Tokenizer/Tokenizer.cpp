#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <regex>
#include <iostream>
#include <fstream>
#include <chrono>
#include <boost\algorithm\string\trim.hpp>
#include "Tokenizer.h"
#include "BadSyntaxException.h"

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

void Tokenizer::tokenize(std::string* input, int size)
{
	
	int lineNumber = 0;
	int syntaxId = -1;
	int level = 0;
	try{
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
								throw BadSyntaxException(lineNumber, linePosition);
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
					throw BadSyntaxException(lineNumber, linePosition);
				}
			}
			input++;
		}
	}
	catch (BadSyntaxException& e){
		std::cout << e.what();
	}
}

void Tokenizer::tokenPartnerCheck(Syntax* syntax, Token* token, int& level, int& linenumber, int& lineposition)
{
	if (syntax->getShouldPush()){
		partnerStack.push(token);
		level++;
	}
	if (syntax->getPartners().size() > 0){
		if (partnerStack.size() == 0){
			throw BadSyntaxException(linenumber, lineposition);
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
		level--;
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

//Uncomment to run tokenizer and test him, remeber to put properties to .exe instead of static .lib and include boost::regex1.56!!!

/*int main(){
	Tokenizer tok;
	std::string line;
	std::vector<std::string> lines;
	std::ifstream file;
	file.open("test code 1.0.txt");
	while (std::getline(file, line)){
		lines.push_back(line);
	}
	file.close();
	auto start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100; i++){
		tok.tokenize(&lines[0], lines.size());
	}
	auto end_time = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
	std::getchar();
	return 0;
}*/
