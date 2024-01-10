#include <iostream>

#include <URL.h>
#include <Ansicolors.h>

#include "CrawlJob.h"
#include "AppArguments.h"

int main(int argc, const char* argv[])
{
	ansicolor::setup_ansi_mode();

#if _DEBUG
	std::cout << "\n\tWarning: THIS IS A " << ansicolor::cyan << "DEBUG" << ansicolor::reset
		<< " BUILD! Performance may be subpar compared to a release build.\n\n";
#endif

	AppArguments args;
	args.parse(argc, argv);

	if (!args.no_banner_flag->is_set)
	{
		std::cout << "WebCrawler by Dylan\n";
	}

	if (args.url->value.empty())
	{
		std::cout << "URL to scan: ";
		std::cin >> args.url->value;
	}

	return 0;
}
