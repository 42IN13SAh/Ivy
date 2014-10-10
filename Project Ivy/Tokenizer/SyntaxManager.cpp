#include "SyntaxManager.h"
#include <iostream>
SyntaxManager::SyntaxManager()
{
	initTokenDictionary();
}

SyntaxManager::~SyntaxManager()
{

}

void SyntaxManager::jsonToSyntaxMap()
{
	Jzon::Array rootNode;
	Jzon::FileReader::ReadFile("Tokens.json", rootNode);
	for (int i = 0; i < rootNode.GetCount(); i++){
		Jzon::Object object = rootNode.Get(i).AsObject();
		int id = object.Get("id").ToInt();
		std::string regexPattern = "^(" + object.Get("regexPattern").ToString() + ")";
		std::string tokenType = object.Get("tokenType").ToString();
		Jzon::Array jsonPartners = object.Get("partners").AsArray();
		std::vector<int> partners;
		for (int i = 0; i < jsonPartners.GetCount(); i++)
		{
			partners.push_back(jsonPartners.Get(i).ToInt());
		}
		Jzon::Array jsonPossibleFollowUps = object.Get("possibleFollowUps").AsArray();
		std::vector<int> possibleFollowUps;
		for (int i = 0; i < jsonPossibleFollowUps.GetCount(); i++)
		{
			possibleFollowUps.push_back(jsonPossibleFollowUps.Get(i).ToInt());
		}
		bool shouldPush = object.Get("shouldPush").ToBool();
		syntaxMap[id] = new Syntax(id, regexPattern, tokenDictionary[tokenType], partners,
			possibleFollowUps, shouldPush);
	}
	fillSyntaxList();
}

void SyntaxManager::fillSyntaxList()
{
	for (auto &iter : syntaxMap)
	{
		syntaxList.push_back(iter.second);
	}
}

std::vector<Syntax*> SyntaxManager::getFollowupVector(int syntaxId)
{
	if (syntaxId != -1)
	{
		std::vector<Syntax*> collection = syntaxMap.find(syntaxId)->second->getPossibleFollowUps(syntaxMap);
		if (collection.size() != 0)
			return collection;
	}
	return syntaxList;
}


std::unordered_map<int, Syntax*> SyntaxManager::getSyntaxMap()
{
	return syntaxMap;
}

void SyntaxManager::initTokenDictionary()
{
	tokenDictionary["IF"] = If;
	tokenDictionary["ELSE"] = Else;
	tokenDictionary["ELSEIF"] = ElseIf;
	tokenDictionary["WHILE"] = While;
	tokenDictionary["DO"] = Do;
	tokenDictionary["FOR"] = For;
	tokenDictionary["FOREACH"] = ForEach;
	tokenDictionary["BRACKET"] = Bracket;
	tokenDictionary["STATEMENTOPERATOR"] = StatementOperator;
	tokenDictionary["ASSIGNMENTOPERATOR"] = AssignmentOperator;
	tokenDictionary["MATHOPERATOR"] = MathOperator;
	tokenDictionary["UNDEFINED"] = Undefined;
	tokenDictionary["LINEEND"] = LineEnd;
	tokenDictionary["FUNCTION"] = Function;
	tokenDictionary["FUNCTIONNAME"] = FunctionName;
	tokenDictionary["VAR"] =  Var;
	tokenDictionary["VARNAME"] = VarName;
	tokenDictionary["RETURN"] = Return;
	tokenDictionary["COMMENT"] = Comment;
	tokenDictionary["PARAMETEROPERATOR"] = ParameterOperator;
	tokenDictionary["NUMBER"] = Number;
	tokenDictionary["STRING"] = String;
	tokenDictionary["BOOLEAN"] = Boolean;
}