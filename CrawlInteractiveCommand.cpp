#include "CrawlInteractiveCommand.h"

#include <iostream>

#include "InteractiveCrawl.h"

void CrawlInteractiveCommand::execute()
{
	program->start_job();
	std::cout << "Please enter a URL: ";
	std::cin >> program->current_job->url;
	std::cout << "Performing job...\n";
	program->do_job();
}