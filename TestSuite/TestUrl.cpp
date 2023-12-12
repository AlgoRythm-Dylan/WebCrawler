#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <memory>

#include <UrlLexer.h>
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
		
		TEST_METHOD(LexerCanParseProtocol)
		{
			string source = "https://";
			UrlLexer lexer(source);
			// Should emit 4 tokens
			auto httpsToken = lexer.next();
			auto colonToken = lexer.next();
			auto firstSlashToken = lexer.next();
			auto secondSlashToken = lexer.next();
			// Make sure none of the pointers are not null
			Assert::IsTrue((bool)httpsToken);
			Assert::IsTrue((bool)colonToken);
			Assert::IsTrue((bool)firstSlashToken);
			Assert::IsTrue((bool)secondSlashToken);
			// Make sure pointers are of correct type
			Assert::AreEqual(httpsToken->type, StdTokenType::str);
			Assert::AreEqual(colonToken->type, StdTokenType::punctuation);
			Assert::AreEqual(firstSlashToken->type, StdTokenType::punctuation);
			Assert::AreEqual(secondSlashToken->type, StdTokenType::punctuation);
			// Make sure pointers have correct value
			Assert::AreEqual(((StringToken*)httpsToken.get())->value, string("https"));
			Assert::AreEqual(((PunctuationToken*)colonToken.get())->value, string(":"));
			Assert::AreEqual(((PunctuationToken*)firstSlashToken.get())->value, string("/"));
			Assert::AreEqual(((PunctuationToken*)secondSlashToken.get())->value, string("/"));
		}
	};
}
