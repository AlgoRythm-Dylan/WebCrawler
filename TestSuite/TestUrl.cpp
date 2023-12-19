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
		TEST_METHOD(AbsoluteWithPathNoEndingSlash)
		{
			string source = "https://www.dylan.com/dylan/skills";
			Url url(source);
			Assert::AreEqual(string("www.dylan.com"), url.host);
			Assert::AreEqual((size_t)3, url.host_parts.size());
			Assert::AreEqual(string("/dylan/skills"), url.path);
			Assert::AreEqual((size_t)2, url.path_parts.size());
		}
		TEST_METHOD(AbsoluteWithPathWithEndingSlash)
		{
			string source = "https://www.dylan.com/dylan/skills/";
			Url url(source);
			Assert::AreEqual(string("www.dylan.com"), url.host);
			Assert::AreEqual((size_t)3, url.host_parts.size());
			Assert::AreEqual(string("/dylan/skills/"), url.path);
			Assert::AreEqual((size_t)2, url.path_parts.size());
		}
		TEST_METHOD(AbsoluteWithQueryNoEndSlashOneParam)
		{
			string source = "https://www.dylan.com/dylan/skills?abc=123";
			Url url(source);
			Assert::AreEqual(string("www.dylan.com"), url.host);
			Assert::AreEqual((size_t)3, url.host_parts.size());
			Assert::AreEqual(string("/dylan/skills"), url.path);
			Assert::AreEqual((size_t)2, url.path_parts.size());
			Assert::AreEqual((size_t)1, url.query_parts.size());
			Assert::AreEqual(string("abc"), url.query_parts[0].key);
			Assert::AreEqual(string("123"), url.query_parts[0].value);
			Assert::AreEqual(string("?abc=123"), url.query);
		}
	};
}