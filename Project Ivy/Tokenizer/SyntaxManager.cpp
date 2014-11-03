#include "SyntaxManager.h"
#include <iostream>
#include <exception>
SyntaxManager::SyntaxManager()
{
	initTokenDictionary();
	initParentDictionary();
}

SyntaxManager::~SyntaxManager()
{
	for each(auto iter in syntaxMap){
		delete iter.second;
	}
}

bool SyntaxManager::hasKeyWord(std::string keyWord)
{
	for (int i = 0; i < reservedKeyWords.size(); i++){
		if (reservedKeyWords[i] == keyWord){
			return true;
		}
	}
	return false;
}

void SyntaxManager::jsonToSyntaxMap()
{
	try{
		Jzon::Array rootNode;
		Jzon::FileReader::ReadFile("tokens.json", rootNode);
		for (int i = 0; i < rootNode.GetCount(); i++){
			Jzon::Object object = rootNode.Get(i).AsObject();
			int id = object.Get("id").ToInt();
			std::string regexPattern = object.Get("regexPattern").ToString();
			std::string tokenType = object.Get("tokenType").ToString();
			std::string parentType = "NULL";
			if (object.Has("parentType")) {
				parentType = object.Get("parentType").ToString();
			}
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
			if (object.Has("reservedKeyWord") && object.Get("reservedKeyWord").ToBool()){
				reservedKeyWords.push_back(object.Get("regexPattern").ToString());
			}
			syntaxMap[id] = new Syntax(id, boost::regex(regexPattern), tokenDictionary[tokenType], parentDictionary[parentType], partners,
				possibleFollowUps, shouldPush);
		}
		fillSyntaxList();
	}
	catch (std::exception& e){
		std::cout << e.what();
	}
}

void SyntaxManager::fillSyntaxList()
{
	for (auto &iter : syntaxMap)
	{
		iter.second->initPartners(syntaxMap);
		iter.second->initFollowUps(syntaxMap);
		syntaxList.push_back(iter.second);
	}
}

std::vector<Syntax*> SyntaxManager::getFollowupVector(int& syntaxId)
{
	if (syntaxId != -1)
	{
		std::vector<Syntax*> collection = syntaxMap.find(syntaxId)->second->getPossibleFollowUps();
		if (collection.size() != 0)
			return collection;
	}
	return syntaxList;
}


std::map<int, Syntax*>* SyntaxManager::getSyntaxMap()
{
	return &syntaxMap;
}

void SyntaxManager::initTokenDictionary()
{
	tokenDictionary["IFSTATEMENT"] = TokenType::IfStatement;
	tokenDictionary["ELSESTATEMENT"] = TokenType::ElseStatement;
	tokenDictionary["WHILESTATEMENT"] = TokenType::WhileStatement;
	tokenDictionary["OPENPARENTHESIS"] = TokenType::OpenParenthesis;
	tokenDictionary["CLOSINGPARENTHESIS"] = TokenType::ClosingParenthesis;
	tokenDictionary["OPENBRACKET"] = TokenType::OpenBracket;
	tokenDictionary["CLOSINGBRACKET"] = TokenType::ClosingBracket;
	tokenDictionary["OPENSQUAREBRACKET"] = TokenType::OpenSquareBracket;
	tokenDictionary["CLOSINGSQUAREBRACKET"] = TokenType::ClosingSquareBracket;
	tokenDictionary["ISNOTSTATEMENT"] = TokenType::IsNotStatement;
	tokenDictionary["ORNOTSTATEMENT"] = TokenType::OrNotStatement;
	tokenDictionary["ISSTATEMENT"] = TokenType::IsStatement;
	tokenDictionary["ANDSTATEMENT"] = TokenType::AndStatement;
	tokenDictionary["NOTSTATEMENT"] = TokenType::NotStatement;
	tokenDictionary["ORSTATEMENT"] = TokenType::OrStatement;
	tokenDictionary["LESSEROREEQUALSTATEMENT"] = TokenType::LesserOrEqualStatement;
	tokenDictionary["GREATHEROREEQUALSTATEMENT"] = TokenType::GreatherOrEqualStatement;
	tokenDictionary["LESSERTHENSTATEMENT"] = TokenType::LesserThenStatement;
	tokenDictionary["GREATHERTHENSTATEMENT"] = TokenType::GreatherThenStatement;
	tokenDictionary["ASSIGNMENTOPERATOR"] = TokenType::AssignmentOperator;
	tokenDictionary["ADDTHENASSIGNOPERATOR"] = TokenType::AddThenAssignOperator;
	tokenDictionary["INCREASEOPERATOR"] = TokenType::IncreaseOperator;
	tokenDictionary["DECREASEOPERATOR"] = TokenType::DecreaseOperator;
	tokenDictionary["ADDOPERATOR"] = TokenType::AddOperator;
	tokenDictionary["MINUSTHENASSIGNOPERATOR"] = TokenType::MinusThenAssignOperator;
	tokenDictionary["DIVIDETHENASSIGNOPERATOR"] = TokenType::DivideThenAssignOperator;
	tokenDictionary["MULTIPLYTHENASSIGNOPERATOR"] = TokenType::MultiplyThenAssignOperator;
	tokenDictionary["MINUSOPERATOR"] = TokenType::MinusOperator;
	tokenDictionary["DIVIDEOPERATOR"] = TokenType::DivideOperator;
	tokenDictionary["MULTIPLYOPERATOR"] = TokenType::MultiplyOperator;
	tokenDictionary["MODULOOPERATOR"] = TokenType::ModuloOperator;
	tokenDictionary["UNDEFINED"] = TokenType::Undefined;
	tokenDictionary["LINEEND"] = TokenType::LineEnd;
	tokenDictionary["FUNCTION"] = TokenType::Function;
	tokenDictionary["VAR"] = TokenType::Var;
	tokenDictionary["RETURN"] = TokenType::Return;
	tokenDictionary["COMMENT"] = TokenType::Comment;
	tokenDictionary["PARAMETEROPERATOR"] = TokenType::ParameterOperator;
	tokenDictionary["NUMBER"] = TokenType::Number;
	tokenDictionary["STRING"] = TokenType::String;
	tokenDictionary["BOOLEANTRUE"] = TokenType::BooleanTrue;
	tokenDictionary["BOOLEANFALSE"] = TokenType::BooleanFalse;
	tokenDictionary["NAME"] = TokenType::Name;
}

void SyntaxManager::initParentDictionary() {
	parentDictionary["MATHOPERATOR"] = ParentType::MathOperator;
	parentDictionary["SUBCONDITIONOPERATOR"] = ParentType::SubConditionOperator;
	parentDictionary["CONDITIONOPERATOR"] = ParentType::ConditionOperator;
	parentDictionary["NULL"] = ParentType::Null;
}
