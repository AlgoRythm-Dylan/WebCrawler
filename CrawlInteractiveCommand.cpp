#include "CrawlInteractiveCommand.h"

#include <iostream>

#include "InteractiveCrawl.h"

void CrawlInteractiveCommand::execute()
{
	auto programPtr = program.lock();

	programPtr->start_job();

	if (args.positionals.size() == 1)
	{
		programPtr->current_job->url = args.positionals[0];
	}
	else
	{
		std::cout << "Please enter a URL: ";
		std::cin >> programPtr->current_job->url;
	}
	std::cout << "Performing job...\n";
	programPtr->do_job();
}