#include <iostream>

#include <URL.h>
#include "Helpers.h"
#include "CrawlJob.h"
#include "AppArguments.h"
#include "AnsiColors.hpp"

int main(int argc, const char* argv[])
{
	ansicolor::setup_ansi_mode();
	
	AppArguments args;
	args.parse(argc, argv);

	if (args.url->value.empty())
	{
		std::cout << "URL to scan: ";
		std::cin >> args.url->value;
	}

	return 0;
}
