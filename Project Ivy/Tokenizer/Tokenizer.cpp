#include <regex>
#include <iostream>
#include <fstream>
#include "Tokenizer.h"
#include "BadSyntaxException.h"
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

void Tokenizer::tokenize(const char* input)
{
	int lineNumber = 1;
	int syntaxId = -1;
	int level = 0;
	const char* unprocessedInput = input;
	try{
		while (*unprocessedInput != '\0'){
			int linePosition = 1;
			unprocessedInput = trim(unprocessedInput, linePosition);
			while (*unprocessedInput != '\n' && *unprocessedInput != '\0'){
				bool hasMatch = false;
				for (Syntax* syntax : syntaxManager.getFollowupVector(syntaxId)){
					std::cmatch result;
					if (std::regex_search(unprocessedInput, result, std::regex(syntax->getRegexPattern()))){
						hasMatch = true;
						Token* token = new Token(syntax->getID(), lineNumber, linePosition, level, result[0], syntax->getTokenType(), nullptr);
						if (token->getTokenType() == Name){
							if (syntaxManager.hasKeyWord(token->getDescription())){
								throw BadSyntaxException(lineNumber, linePosition);
							}
						}
						tokenList.push_back(token);
						tokenPartnerCheck(syntax, token, level);
						linePosition += result[0].length();
						unprocessedInput += result[0].length();
						unprocessedInput = trim(unprocessedInput, linePosition);
						syntaxId = syntax->getID();
						break;
					}
				}
				if (!hasMatch){
					Syntax* syntax = syntaxManager.getSyntaxMap()[syntaxId];
					throw BadSyntaxException(lineNumber, linePosition);
				}
			}
			if (*unprocessedInput != '\0'){
				unprocessedInput++;
				lineNumber++;
			}
		}
	}
	catch (BadSyntaxException& e){
		std::cout << e.what();
	}
}

void Tokenizer::tokenPartnerCheck(Syntax* syntax, Token* token, int& level)
{
	if (syntax->getShouldPush()){
		partnerStack.push(token);
		level++;
	}
	if (syntax->getPartners(syntaxManager.getSyntaxMap()).size() > 0){
		Token* stackToken = partnerStack.top();
		partnerStack.pop();
		if (token->getTokenType() == TokenType::ClosingBracket){
			while (stackToken->getTokenType() == TokenType::If){
				stackToken = partnerStack.top();
				partnerStack.pop();
			}
		}
		for (Syntax* partner : syntax->getPartners(syntaxManager.getSyntaxMap())){
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

int main(){
	Tokenizer tok;
	std::ifstream file("test code 1.0.txt", std::ios::in | std::ios::binary| std::ios::ate);
	const char* input = "";
	if (file.is_open()){
		file.seekg(0, std::ios::end);
		int size = file.tellg();
		char* temp = new char[size];
		file.seekg(std::ios::beg);
		file.read(temp, size);
		input = temp;
		file.close();
	}
	tok.tokenize("var x = 10");
	return 0;
}