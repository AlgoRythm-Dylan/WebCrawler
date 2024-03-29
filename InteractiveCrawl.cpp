#include "InteractiveCrawl.h"

#include <iostream>

#include <AnsiColors.h>
#include <Arguments.h>

#include "CrawlJob.h"
#include "HeadersInteractiveCommand.h"
#include "CrawlInteractiveCommand.h"
#include "PrintInteractiveCommand.h"
#include "StatsInteractiveCommand.h"

InteractiveCrawl::InteractiveCrawl()
{
	auto headersCommand = std::make_shared<InteractiveCommandCreator>();
	headersCommand->name = "headers";
	headersCommand->description = "View the headers of the most recent job";
	headersCommand->creator = []() -> shared_ptr<InteractiveCommand> {
		return shared_ptr<InteractiveCommand>(new HeadersInteractiveCommand());
	};
	commands.push_back(headersCommand);

	auto crawlCommand = std::make_shared<InteractiveCommandCreator>();
	crawlCommand->name = "crawl";
	crawlCommand->requires_valid_response = false;
	crawlCommand->description = "Set the currently crawling page";
	crawlCommand->creator = []() -> shared_ptr<InteractiveCommand> {
		return shared_ptr<InteractiveCommand>(new CrawlInteractiveCommand());
	};
	commands.push_back(crawlCommand);

	auto printCommand = std::make_shared<InteractiveCommandCreator>();
	printCommand->name = "print";
	printCommand->description = "Display the content of the crawled page";
	printCommand->creator = []() -> shared_ptr<InteractiveCommand> {
		return shared_ptr<InteractiveCommand>(new PrintInteractiveCommand());
	};
	commands.push_back(printCommand);

	auto statsCommand = std::make_shared<InteractiveCommandCreator>();
	statsCommand->name = "stats";
	statsCommand->description = "Display the stats of the crawled page";
	statsCommand->creator = []() -> shared_ptr<InteractiveCommand> {
		return shared_ptr<InteractiveCommand>(new StatsInteractiveCommand());
	};
	commands.push_back(statsCommand);
}

void InteractiveCrawl::execute()
{
	start_job();
	query_url();
	do_job();
	start_interactive_prompt();
}

void InteractiveCrawl::query_url()
{

	auto appPtr = app.lock();

	if (appPtr->url.has_value())
	{
		current_job->url = appPtr->url.value();
		std::cout << "Using URL " << current_job->url << "\n";
		// Consume the app URL so it doesn't get used next time
		appPtr->url.reset();
	}
	else
	{
		std::cout << "Please enter an initial URL: ";
		std::getline(std::cin, current_job->url);
	}
}

void InteractiveCrawl::start_job()
{
	auto appPtr = app.lock();

	current_job = std::make_unique<CrawlJob>();
	current_job->user_agent = appPtr->user_agent.value();
}

void InteractiveCrawl::do_job()
{
	auto appPtr = app.lock();

	current_job->perform();

	if (current_job->response->has_curl_error())
	{
		std::cout << "Unable to complete request: ";
		if (!current_job->response->error_message.empty())
		{
			std::cout << current_job->response->error_message << "\n";
		}
		else
		{
			std::cout << "Unknown Error.\n";
		}
		return;
	}
	else
	{
		std::cout << "Job complete. Return code: ";
		if (appPtr->colors)
		{
			std::cout << ansicolor::magenta;
		}
		std::cout << current_job->response->status;
		if (appPtr->colors)
		{
			std::cout << ansicolor::reset;
		}
		std::cout << "\n";
		if (current_job->response->status == 301 || current_job->response->status == 302)
		{
			auto locationHeaderSearch = current_job->response->search_headers_insensitive("Location");
			if (!locationHeaderSearch.empty()) {
				string location = locationHeaderSearch[0].second;
				std::cout << "Redirect code returned pointing to location: ";
				if (appPtr->colors)
				{
					std::cout << ansicolor::yellow;
				}
				std::cout << location;
				if (appPtr->colors)
				{
					std::cout << ansicolor::reset;
				}
				std::cout << "\nFollow redirect? [y/n]: ";
				string response;
				std::getline(std::cin, response);
				if (response == "y" || response == "Y")
				{
					start_job();
					current_job->url = location;
					do_job();
				}
			}
			else
			{
				std::cout << "Redirect code returned - but no location"
					<< " header provided. Check headers.\n";
			}
		}
	}
}

shared_ptr<InteractiveCommandCreator> InteractiveCrawl::find_command(string_view name)
{
	for (int i = 0; i < commands.size(); i++)
	{
		if (commands[i]->name == name)
		{
			return commands[i];
		}
	}
	return nullptr;
}

void InteractiveCrawl::start_interactive_prompt()
{
	while (true)
	{
		string input;
		std::cout << "interactive> ";
		std::getline(std::cin, input);
		if (input.empty())
		{
			continue;
		}
		auto sysargs = Arguments::parse_from_string(input);
		if (sysargs->argv[0] == string("exit"))
		{
			break;
		}
		auto commandCreator = find_command(sysargs->argv[0]);
		if (commandCreator)
		{
			if (commandCreator->requires_valid_response)
			{
				if (!current_job->response->was_success())
				{
					std::cout << "This command will not execute because the HTTP request was not successful.\n";
					continue;
				}
			}
			auto command = commandCreator->creator();
			command->program = shared_from_this();
			command->args.parse(sysargs->argc, sysargs->argv);
			command->execute();
		}
		else
		{
			std::cout << "Unknown command: \"" << sysargs->argv[0] << "\"\n";
		}
	}
}