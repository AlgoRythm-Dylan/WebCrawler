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
	TEST_CLASS(TestUrlParse)
	{
	public:
		TEST_METHOD(CanParseEmptyString)
		{
			string source = "";
			Url url;
			UrlLexer lexer(source);
			UrlParser parser(url);
			parser.scan(lexer.next());
		}
		TEST_METHOD(CanParseProtocol)
		{
			string source = "https://";
			Url url;
			UrlLexer lexer(source);
			UrlParser parser(url);
			for (int i = 0; i < 3; i++)
			{
				auto tok = lexer.next();
				parser.scan(std::move(tok));
			}
			Assert::AreEqual(string("https"), url.protocol);
		}
	};
}