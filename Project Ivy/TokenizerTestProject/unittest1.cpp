#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Tokenizer\SyntaxManager.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TokenizerTestProject
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			SyntaxManager t;
			t.jsonToSyntaxMap();
		}

	};
}