#include "pch.h"
#include "CppUnitTest.h"

#include <string>

#include <LexingTools.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestSuite
{
	TEST_CLASS(TestLexingTools)
	{
	public:
		TEST_METHOD(IsNumericTrue)
		{
			Assert::IsTrue(LexingTools::is_numeric("123"));
		}
		TEST_METHOD(IsNumericFalse)
		{
			Assert::IsFalse(LexingTools::is_numeric("abc123"));
		}
	};
}