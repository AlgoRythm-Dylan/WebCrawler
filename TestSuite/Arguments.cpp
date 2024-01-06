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
			int argc = 6;
			const char* argv[6] = {
				"WebCrawler.exe",
				"-test",
				"--key=value",
				"--long-flag",
				"positionals",
				"suck"
			};
			Arguments args;
			args.parse(argc, argv);
			Assert::IsTrue(args.flags.contains('t'));
		}
	};
}