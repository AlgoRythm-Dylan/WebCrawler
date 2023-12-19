#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <memory>

#include <UrlLexer.h>
#include <UrlParser.h>
#include <Token.h>
#include <StringToken.h>
#include <PunctuationToken.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace TestSuite
{
	TEST_CLASS(TestUrl)
	{
	public:
		TEST_METHOD(AbsoluteNoPasswordNoPath)
		{
			string source = "https://www.dylan.com";
			Url url(source);
			Assert::AreEqual(string("www.dylan.com"), url.host);
			Assert::AreEqual((size_t)3, url.host_parts.size());
		}
		TEST_METHOD(AbsoluteWithPasswordNoPath)
		{
			string source = "https://dylan:password@www.dylan.com";
			Url url(source);
			Assert::AreEqual(string("www.dylan.com"), url.host);
			Assert::AreEqual((size_t)3, url.host_parts.size());
			Assert::AreEqual(string("dylan"), url.username);
			Assert::AreEqual(string("password"), url.password);
		}
	};
}