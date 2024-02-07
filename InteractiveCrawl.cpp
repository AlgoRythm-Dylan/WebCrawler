#include "InteractiveCrawl.h"

#include <iostream>

#include <AnsiColors.h>

#include "CrawlJob.h"

void InteractiveCrawl::execute()
{
	query_url();
	current_job.user_agent = app->user_agent.value();
	do_job();
	prompt_user();
}

void InteractiveCrawl::query_url()
{
	if (app->url.has_value())
	{
		current_job.url = app->url.value();
		std::cout << "Using URL " << current_job.url << "\n";
		// Consume the app URL so it doesn't get used next time
		app->url.reset();
	}
	else
	{
		std::cout << "Please enter an initial URL: ";
		std::cin >> current_job.url;
	}
}

void InteractiveCrawl::do_job()
{
	current_job.perform();
	std::cout << "Job complete. Return code: ";
	if (app->colors)
	{
		std::cout << ansicolor::magenta;
	}
	std::cout << current_job.response->status;
	if (app->colors)
	{
		std::cout << ansicolor::reset;
	}
	std::cout << "\n";
}

void InteractiveCrawl::prompt_user()
{
	string input;
	std::cout << "interactive> ";
	std::cin >> input;
}