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
			auto eofToken = lexer.next();
			// Make sure none of the pointers are not null
			Assert::IsTrue((bool)httpsToken);
			Assert::IsTrue((bool)colonToken);
			Assert::IsTrue((bool)firstSlashToken);
			Assert::IsTrue((bool)secondSlashToken);
			Assert::IsTrue((bool)eofToken);
			// Make sure pointers are of correct type
			Assert::AreEqual(StdTokenType::str, httpsToken->type);
			Assert::AreEqual(StdTokenType::punctuation, colonToken->type);
			Assert::AreEqual(StdTokenType::punctuation, firstSlashToken->type);
			Assert::AreEqual(StdTokenType::punctuation, secondSlashToken->type);
			Assert::AreEqual(StdTokenType::end, eofToken->type);
			// Make sure pointers have correct value
			Assert::AreEqual(string("https"), ((StringToken*)httpsToken.get())->value);
			Assert::AreEqual(string(":"), ((PunctuationToken*)colonToken.get())->value);
			Assert::AreEqual(string("/"), ((PunctuationToken*)firstSlashToken.get())->value);
			Assert::AreEqual(string("/"), ((PunctuationToken*)secondSlashToken.get())->value);
		}
	};
}
