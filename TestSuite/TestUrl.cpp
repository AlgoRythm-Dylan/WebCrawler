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

		TEST_METHOD(CanLexAbsoluteRelativePath)
		{
			// "absolute-relative" path is a path that starts
			// with root, but is still relative to the current
			// domain
			string source = "/hello/world";
			UrlLexer lexer(source);
			// Should emit 4 tokens: 2 punctuation, 2 str
			auto firstSlashToken = lexer.next();
			auto firstPathToken = lexer.next();
			auto secondSlashToken = lexer.next();
			auto secondPathToken = lexer.next();
			auto eofToken = lexer.next();
			// Check the tokens are created
			Assert::IsTrue((bool)firstSlashToken);
			Assert::IsTrue((bool)firstPathToken);
			Assert::IsTrue((bool)secondSlashToken);
			Assert::IsTrue((bool)secondPathToken);
			Assert::IsTrue((bool)eofToken);
			// Check token types
			Assert::AreEqual(StdTokenType::punctuation, firstSlashToken->type);
			Assert::AreEqual(StdTokenType::str, firstPathToken->type);
			Assert::AreEqual(StdTokenType::punctuation, secondSlashToken->type);
			Assert::AreEqual(StdTokenType::str, secondPathToken->type);
			Assert::AreEqual(StdTokenType::end, eofToken->type);
			// Check token values
			Assert::AreEqual(string("/"), ((PunctuationToken*)firstSlashToken.get())->value);
			Assert::AreEqual(string("hello"), ((StringToken*)firstPathToken.get())->value);
			Assert::AreEqual(string("/"), ((PunctuationToken*)secondSlashToken.get())->value);
			Assert::AreEqual(string("world"), ((StringToken*)secondPathToken.get())->value);
		}
	};
}
