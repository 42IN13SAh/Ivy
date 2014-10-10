#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Tokenizer\Tokenizer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TokenizerTestProject
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(Given_Valid_String_Then_TokenList_Should_Be_Filled_Properly)
		{
			// TODO: Your test code here
			std::string* input = new std::string("var x = 5; function x(); if (x = 3)");
			Tokenizer* t = new Tokenizer();
			t->tokenize(input, 1);
			std::list<Token*> tokenList = t->getTokenList();
			Assert::AreEqual(std::string("var"), tokenList.front()->getDescription(), L"Given_Valid_String_Then_TokenList_Should_Be_Filled_Properly Faalt", LINE_INFO());
		}

	};
}