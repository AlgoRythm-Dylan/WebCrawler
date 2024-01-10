#include <iostream>

#include <URL.h>
#include <Ansicolors.h>

#include "CrawlJob.h"
#include "AppArguments.h"

int main(int argc, const char* argv[])
{
	ansicolor::setup_ansi_mode();
	
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
