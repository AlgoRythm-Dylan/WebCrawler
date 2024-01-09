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
			int argc = 2;
			const char* argv[2] = {
				"WebCrawler.exe",
				"-te"
			};

			Arguments args;

			auto shortFlagT = shared_ptr<Argument>(Argument::flag('t'));
			auto shortFlagE = shared_ptr<Argument>(Argument::flag('e'));
			auto shortFlagS = shared_ptr<Argument>(Argument::flag('s'));

			args.add_argument(shortFlagT);
			args.add_argument(shortFlagE);
			args.add_argument(shortFlagS);

			args.parse(argc, argv);

			Assert::IsTrue(shortFlagT->is_set);
			Assert::IsTrue(shortFlagE->is_set);
			Assert::IsFalse(shortFlagS->is_set);
		}
	};
}