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
			constexpr int argc = 3;
			const char* argv[argc] = {
				"WebCrawler.exe",
				"-te",
				"--long-flag"
			};

			Arguments args;

			auto shortFlagT = shared_ptr<Argument>(Argument::flag('t'));
			auto shortFlagE = shared_ptr<Argument>(Argument::flag('e'));
			auto shortFlagS = shared_ptr<Argument>(Argument::flag('s'));
			auto longFlag = shared_ptr<Argument>(Argument::flag("long-flag"));

			args.add_argument(shortFlagT);
			args.add_argument(shortFlagE);
			args.add_argument(shortFlagS);
			args.add_argument(longFlag);

			args.parse(argc, argv);

			Assert::IsTrue(shortFlagT->is_set);
			Assert::IsTrue(shortFlagE->is_set);
			Assert::IsFalse(shortFlagS->is_set);
			Assert::IsTrue(longFlag->is_set);
		}
	};
}