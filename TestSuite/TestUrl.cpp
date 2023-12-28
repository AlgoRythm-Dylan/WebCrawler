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
			Assert::IsFalse(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(0, url.port);
			Assert::AreEqual(string("www.dylan.com"), url.host);
			Assert::AreEqual((size_t)3, url.host_parts.size());
		}
		TEST_METHOD(AbsoluteWithPasswordNoPath)
		{
			string source = "https://dylan:password@www.dylan.com";
			Url url(source);
			Assert::IsFalse(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(0, url.port);
			Assert::AreEqual(string("www.dylan.com"), url.host);
			Assert::AreEqual((size_t)3, url.host_parts.size());
			Assert::AreEqual(string("dylan"), url.username);
			Assert::AreEqual(string("password"), url.password);
		}
		TEST_METHOD(AbsoluteWithPathNoEndingSlash)
		{
			string source = "https://www.dylan.com/dylan/skills";
			Url url(source);
			Assert::IsFalse(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(0, url.port);
			Assert::AreEqual(string("www.dylan.com"), url.host);
			Assert::AreEqual((size_t)3, url.host_parts.size());
			Assert::AreEqual(string("/dylan/skills"), url.path);
			Assert::AreEqual((size_t)2, url.path_parts.size());
		}
		TEST_METHOD(AbsoluteWithPathWithEndingSlash)
		{
			string source = "https://www.dylan.com/dylan/skills/";
			Url url(source);
			Assert::IsFalse(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(0, url.port);
			Assert::AreEqual(string("www.dylan.com"), url.host);
			Assert::AreEqual((size_t)3, url.host_parts.size());
			Assert::AreEqual(string("/dylan/skills/"), url.path);
			Assert::AreEqual((size_t)2, url.path_parts.size());
		}
		TEST_METHOD(AbsoluteWithQueryNoEndSlashOneParam)
		{
			string source = "https://www.dylan.com/dylan/skills?abc=123";
			Url url(source);
			Assert::IsFalse(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(0, url.port);
			Assert::AreEqual(string("www.dylan.com"), url.host);
			Assert::AreEqual((size_t)3, url.host_parts.size());
			Assert::AreEqual(string("/dylan/skills"), url.path);
			Assert::AreEqual((size_t)2, url.path_parts.size());
			Assert::AreEqual((size_t)1, url.query_parts.size());
			Assert::AreEqual(string("abc"), url.query_parts[0].key);
			Assert::AreEqual(string("123"), url.query_parts[0].value);
			Assert::AreEqual(string("?abc=123"), url.query);
		}
		TEST_METHOD(SimpleRelative)
		{
			string source = "page";
			Url url(source);
			Assert::IsTrue(url.is_relative);
			Assert::IsTrue(url.is_valid);
			Assert::IsFalse(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(0, url.port);
			Assert::AreEqual((size_t)0, url.host_parts.size());
			Assert::AreEqual(string("page"), url.path);
			Assert::AreEqual((size_t)1, url.path_parts.size());
			Assert::AreEqual(string("page"), url.path_parts[0]);
		}
		TEST_METHOD(RelativeWithPath)
		{
			string source = "resource/action";
			Url url(source);
			Assert::IsTrue(url.is_relative);
			Assert::IsTrue(url.is_valid);
			Assert::IsFalse(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(0, url.port);
			Assert::AreEqual((size_t)0, url.host_parts.size());
			Assert::AreEqual(string("resource/action"), url.path);
			Assert::AreEqual((size_t)2, url.path_parts.size());
			Assert::AreEqual(string("resource"), url.path_parts[0]);
			Assert::AreEqual(string("action"), url.path_parts[1]);
		}
		TEST_METHOD(RelativeWithFragment)
		{
			string source = "resource#section";
			Url url(source);
			Assert::IsTrue(url.is_relative);
			Assert::IsTrue(url.is_valid);
			Assert::IsFalse(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(0, url.port);
			Assert::AreEqual((size_t)0, url.host_parts.size());
			Assert::AreEqual(string("resource"), url.path);
			Assert::AreEqual(string("section"), url.fragment);
			Assert::AreEqual((size_t)1, url.path_parts.size());
			Assert::AreEqual(string("resource"), url.path_parts[0]);
		}
		TEST_METHOD(RelativeWithQuery)
		{
			string source = "resource?query=val";
			Url url(source);
			Assert::IsTrue(url.is_relative);
			Assert::IsTrue(url.is_valid);
			Assert::IsFalse(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(0, url.port);
			Assert::AreEqual((size_t)0, url.host_parts.size());
			Assert::AreEqual(string("resource"), url.path);
			Assert::AreEqual(string("?query=val"), url.query);
			Assert::AreEqual((size_t)1, url.query_parts.size());
			Assert::AreEqual(string("query"), url.query_parts[0].key);
			Assert::AreEqual(string("val"), url.query_parts[0].value);
		}
		TEST_METHOD(RelativeWithQueryAndFragment)
		{
			string source = "resource?query=val#section";
			Url url(source);
			Assert::IsTrue(url.is_relative);
			Assert::IsTrue(url.is_valid);
			Assert::IsFalse(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(0, url.port);
			Assert::AreEqual((size_t)0, url.host_parts.size());
			Assert::AreEqual(string("resource"), url.path);
			Assert::AreEqual(string("?query=val"), url.query);
			Assert::AreEqual(string("section"), url.fragment);
			Assert::AreEqual((size_t)1, url.query_parts.size());
			Assert::AreEqual(string("query"), url.query_parts[0].key);
			Assert::AreEqual(string("val"), url.query_parts[0].value);
		}
		TEST_METHOD(RelativeWithPathQueryAndFragment)
		{
			string source = "resource/action?query=val#section";
			Url url(source);
			Assert::IsTrue(url.is_relative);
			Assert::IsTrue(url.is_valid);
			Assert::IsFalse(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(0, url.port);
			Assert::AreEqual((size_t)0, url.host_parts.size());
			Assert::AreEqual(string("resource/action"), url.path);
			Assert::AreEqual(string("?query=val"), url.query);
			Assert::AreEqual(string("section"), url.fragment);
			Assert::AreEqual((size_t)1, url.query_parts.size());
			Assert::AreEqual(string("query"), url.query_parts[0].key);
			Assert::AreEqual(string("val"), url.query_parts[0].value);
			Assert::AreEqual((size_t)2, url.path_parts.size());
			Assert::AreEqual(string("resource"), url.path_parts[0]);
			Assert::AreEqual(string("action"), url.path_parts[1]);
		}
		TEST_METHOD(IPV4PostiveDetection)
		{
			string source = "http://192.168.1.1";
			Url url(source);
			Assert::IsTrue(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(0, url.port);
		}
		TEST_METHOD(IPV4NegativeDetection)
		{
			string source = "http://192.168.0.1";
			Url url(source);
			Assert::IsFalse(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(0, url.port);
		}
		TEST_METHOD(PortSimple)
		{
			string source = "http://localhost:3000";
			Url url(source);
			Assert::IsTrue(url.is_valid);
			Assert::IsFalse(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(3000, url.port);
			Assert::AreEqual(string("localhost"), url.host);
		}
		TEST_METHOD(IPV6Positive)
		{
			string source = "http://[2001:db8:2a:3256:adfe:5c0:3:6]:3000";
			Url url(source);
			Assert::IsTrue(url.is_valid);
			Assert::IsFalse(url.is_ipv4);
			Assert::IsTrue(url.is_ipv6);
			Assert::AreEqual(3000, url.port);
			Assert::AreEqual(string("[2001:db8:2a:3256:adfe:5c0:3:6]"), url.host);
			Assert::AreEqual((size_t)8, url.host_parts.size());
		}
		TEST_METHOD(IPV6Negative)
		{
			string source = "http://localhost:3000";
			Url url(source);
			Assert::IsTrue(url.is_valid);
			Assert::IsFalse(url.is_ipv4);
			Assert::IsFalse(url.is_ipv6);
			Assert::AreEqual(3000, url.port);
			Assert::AreEqual(string("localhost"), url.host);
		}
	};
}