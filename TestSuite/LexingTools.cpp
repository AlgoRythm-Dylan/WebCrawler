#include "pch.h"
#include "CppUnitTest.h"

#include <string>

#include <LexingTools.h>
#include <StringTracker.h>

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
		TEST_METHOD(StringTrackerTest)
		{
			StringTracker tracker("</script>");
			Assert::IsFalse(tracker.add('a'));
			Assert::IsTrue(tracker.add('<'));
			Assert::IsFalse(tracker.is_match());
			Assert::IsTrue(tracker.add('/'));
			Assert::IsTrue(tracker.add('s'));
			Assert::IsTrue(tracker.add('c'));
			Assert::IsTrue(tracker.add('r'));
			Assert::IsTrue(tracker.add('i'));
			Assert::IsTrue(tracker.add('p'));
			Assert::IsTrue(tracker.add('t'));
			Assert::IsTrue(tracker.add('>'));
			Assert::IsTrue(tracker.is_match());
		}
	};
}