#include "pch.h"
#include "CppUnitTest.h"

#include <string>

#include <Arguments.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestSuite
{
	TEST_CLASS(TestArgumentsTools)
	{
	public:
		TEST_METHOD(ArgumentsWork)
		{
			constexpr int argc = 10;
			const char* argv[argc] = {
				"WebCrawler.exe",
				"-te",
				"--long-flag",
				"--inline-kv=value",
				"--key-value",
				"pair",
				"--header",
				"Content-Type: application/json",
				"--header",
				"User-Agent: real-browser-i-swear"
			};

			Arguments args;

			auto shortFlagT = shared_ptr<Argument>(Argument::flag('t'));
			auto shortFlagE = shared_ptr<Argument>(Argument::flag('e'));
			auto shortFlagS = shared_ptr<Argument>(Argument::flag('s'));
			auto longFlag = shared_ptr<Argument>(Argument::flag("long-flag"));
			auto inlineKV = shared_ptr<Argument>(Argument::key_value("inline-kv"));
			auto kvp = shared_ptr<Argument>(Argument::key_value("key-value"));
			auto kvl = shared_ptr<Argument>(Argument::key_value_list("header"));

			args.add_argument(shortFlagT);
			args.add_argument(shortFlagE);
			args.add_argument(shortFlagS);
			args.add_argument(longFlag);
			args.add_argument(inlineKV);
			args.add_argument(kvp);
			args.add_argument(kvl);

			args.parse(argc, argv);

			Assert::IsTrue(shortFlagT->is_set);
			Assert::IsTrue(shortFlagE->is_set);
			Assert::IsFalse(shortFlagS->is_set);
			Assert::AreEqual(string("value"), inlineKV->value);
			Assert::AreEqual(string("pair"), kvp->value);
			Assert::AreEqual((size_t)2, kvl->values.size());
			Assert::AreEqual(string("Content-Type: application/json"), kvl->values[0]);
			Assert::AreEqual(string("User-Agent: real-browser-i-swear"), kvl->values[1]);
		}
		TEST_METHOD(ArgsFromString)
		{
			string source = "WebCrawler.exe abc 123 \"hello world\"";
			auto parsed = Arguments::parse_from_string(source);

			Assert::AreEqual(4, parsed->argc);
			Assert::AreEqual("WebCrawler.exe", parsed->argv[0]);
			Assert::AreEqual("abc", parsed->argv[1]);
			Assert::AreEqual("123", parsed->argv[2]);
			Assert::AreEqual("hello world", parsed->argv[3]);
		}
	};
}