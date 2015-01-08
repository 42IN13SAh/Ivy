#pragma once
#include <vector>
#include <string>
#include "SyntaxManager.h"
#include "TokenType.h"
#include "BaseException.h"

class BadMatchException : public BaseException
{
public:
	BadMatchException(int lnr, int lps, int sid) : BaseException(lnr, lps) { }
	virtual ~BadMatchException(){}

	virtual const std::vector<std::string> getFollowUps(int &sid) {
		return getSyntaxValuesAsString(SyntaxManager::Instance()->getFollowupVector(sid));
	}

	virtual const std::vector<std::string> getPartners(int &sid) {
		return getSyntaxValuesAsString(SyntaxManager::Instance()->getSyntax(sid)->getPartners());
	}

	virtual const std::vector<std::string> getSyntaxValuesAsString(std::vector<Syntax*> sVec) {
		std::vector<std::string> strVec;
		for each(Syntax* s in sVec) {
			strVec.push_back(TokenType::TokenTypeNames[s->getTokenType()]);
		}

		return strVec;
	}
};