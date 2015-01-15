#include <stdlib.h>
#include <crtdbg.h>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <regex>
#include <fstream>
#include <chrono>
#include "Tokenizer.h"
#include "BadSyntaxException.h"
#include "PartnerNotFoundException.h"
#include "ReservedKeywordException.h"

Tokenizer::Tokenizer()
{
	//SyntaxManager::Instance()->jsonToSyntaxMap();
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

const std::vector<BaseException>& Tokenizer::getErrorList() {
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
			for (Syntax* syntax : SyntaxManager::Instance()->getFollowupVector(syntaxId)){
				boost::cmatch result;
				if (boost::regex_search(unprocessedInput, result, syntax->getRegexPattern(), boost::match_continuous)){
					hasMatch = true;
					std::string res(result[0]);
					if (syntax->getTokenType() == TokenType::String) {
						res.erase(res.begin());
						res.erase(res.end()-1);
					}
					Token* token = new Token(syntax->getID(), lineNumber, linePosition, level, res, syntax->getTokenType(), syntax->getParentType(), nullptr);
					if (token->getTokenType() == TokenType::Name){
						if (SyntaxManager::Instance()->hasKeyWord(token->getDescription())){
							//throw ReservedKeywordException(token->getDescription(), lineNumber, linePosition);
							errorList.push_back(ReservedKeywordException(lineNumber, linePosition, token->getDescription()));
							unprocessedInput += token->getDescription().length();
							delete token;
							break;
						}
					}
					if (!tokenPartnerCheck(syntax, token, level, lineNumber, linePosition)) {
						unprocessedInput++;
						delete token;
						break;
					}
					
					linePosition += result[0].length();
					unprocessedInput += result[0].length();
					unprocessedInput = trim(unprocessedInput, linePosition);
					if (token->getTokenType() != TokenType::Comment) {
						tokenList.push_back(token);
						syntaxId = syntax->getID();
					}
					break;
				}
			}
			if (!hasMatch){
				//throw BadSyntaxException(lineNumber, linePosition);
				errorList.push_back(BadSyntaxException(lineNumber, linePosition, syntaxId, (tokenList.size()) ? tokenList.back()->getDescription() : unprocessedInput));
				// Check until space, if found chars is a name or word, skip that much positions
				unprocessedInput = trim(++unprocessedInput, linePosition);
			}
		}
		input++;
	}
	while (!partnerStack.empty()) {
		Token* t = partnerStack.top();
		partnerStack.pop();
		if (t->getTokenType() != TokenType::IfStatement) {
			errorList.push_back(PartnerNotFoundException(t->getLineNumber(), t->getLinePosition(), t->getSyntaxID(), t->getDescription()));
		}
	}
}

bool Tokenizer::tokenPartnerCheck(Syntax* syntax, Token* token, int& level, int& linenumber, int& lineposition)
{
	if (syntax->getShouldPush()){
		partnerStack.push(token);
		if (token->getTokenType() != TokenType::IfStatement)
			level++;
	}
	if (syntax->getPartners().size() > 0){
		if (partnerStack.size() == 0){
			//throw PartnerNotFoundException(token->getDescription(), linenumber, lineposition);
			errorList.push_back(PartnerNotFoundException(linenumber, lineposition, syntax->getID(), token->getDescription()));
			return false;
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
	return true;
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
