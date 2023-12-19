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
		TEST_METHOD(CanParseAbsoluteWithDomain)
		{
			string source = "https://www.dylan.com";
			Url url;
			UrlLexer lexer(source);
			UrlParser parser(url);
			// "https"
			auto protocolNameTok = lexer.next();
			Assert::AreEqual(StdTokenType::str, protocolNameTok->type);
			parser.scan(std::move(protocolNameTok));
			// ":" - transition to punctuation parse state, returns token
			auto protocolColonTok = lexer.next();
			Assert::AreEqual(StdTokenType::punctuation, protocolColonTok->type);
			protocolColonTok = parser.scan(std::move(protocolColonTok));
			// new state re-scans ":"
			Assert::AreEqual(StdTokenType::punctuation, protocolColonTok->type);
			parser.scan(std::move(protocolColonTok));
			// "/"
			auto firstSlashProtocolTok = lexer.next();
			Assert::AreEqual(StdTokenType::punctuation, firstSlashProtocolTok->type);
			parser.scan(std::move(firstSlashProtocolTok));
			// "/" - state transitions to authority parsing state
			auto secondSlashProtocolTok = lexer.next();
			Assert::AreEqual(StdTokenType::punctuation, secondSlashProtocolTok->type);
			parser.scan(std::move(secondSlashProtocolTok));
			// "www"
			auto wwwStrTok = lexer.next();
			Assert::AreEqual(StdTokenType::str, wwwStrTok->type);
			Assert::AreEqual(string("www"), ((StringToken*)wwwStrTok.get())->value);
			parser.scan(std::move(wwwStrTok));
			// "."
			auto firstDotTok = lexer.next();
			Assert::AreEqual(StdTokenType::punctuation, firstDotTok->type);
			parser.scan(std::move(firstDotTok));
			// "dylan"
			auto dylanStrTok = lexer.next();
			Assert::AreEqual(StdTokenType::str, dylanStrTok->type);
			Assert::AreEqual(string("dylan"), ((StringToken*)dylanStrTok.get())->value);
			parser.scan(std::move(dylanStrTok));
			// "."
			auto secondDotTok = lexer.next();
			Assert::AreEqual(StdTokenType::punctuation, secondDotTok->type);
			parser.scan(std::move(secondDotTok));
			// "com"
			auto comStrTok = lexer.next();
			Assert::AreEqual(StdTokenType::str, comStrTok->type);
			Assert::AreEqual(string("com"), ((StringToken*)comStrTok.get())->value);
			parser.scan(std::move(comStrTok));
			// EOF
			auto endTok = lexer.next();
			Assert::AreEqual(StdTokenType::end, endTok->type);
			parser.scan(std::move(endTok));
			Assert::AreEqual(string("https"), url.protocol);
			Assert::AreEqual(string("www.dylan.com"), url.host);
		}
		TEST_METHOD(UrlCanParseAuthority)
		{
			string source = "https://dylan:password@www.dylan.com";
			Url url(source);
		}
	};
}