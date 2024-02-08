#include "InteractiveCrawl.h"

#include <iostream>

#include <AnsiColors.h>
#include <Arguments.h>

#include "CrawlJob.h"
#include "HeadersInteractiveCommand.h"

InteractiveCrawl::InteractiveCrawl()
{
	auto headersCommand = std::make_shared<InteractiveCommandCreator>();
	headersCommand->name = "headers";
	headersCommand->description = "View the headers of the most recent job";
	headersCommand->creator = []() -> shared_ptr<InteractiveCommand> {
		return shared_ptr<InteractiveCommand>(new HeadersInteractiveCommand());
	};
	commands.push_back(headersCommand);
}

void InteractiveCrawl::execute()
{
	start_job();
	query_url();
	current_job->user_agent = app->user_agent.value();
	do_job();
	start_interactive_prompt();
}

void InteractiveCrawl::query_url()
{
	if (app->url.has_value())
	{
		current_job->url = app->url.value();
		std::cout << "Using URL " << current_job->url << "\n";
		// Consume the app URL so it doesn't get used next time
		app->url.reset();
	}
	else
	{
		std::cout << "Please enter an initial URL: ";
		std::cin >> current_job->url;
	}
}

void InteractiveCrawl::start_job()
{
	current_job = std::make_unique<CrawlJob>();
}

void InteractiveCrawl::do_job()
{
	current_job->perform();
	std::cout << "Job complete. Return code: ";
	if (app->colors)
	{
		std::cout << ansicolor::magenta;
	}
	std::cout << current_job->response->status;
	if (app->colors)
	{
		std::cout << ansicolor::reset;
	}
	std::cout << "\n";
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
		std::cin >> input;
		auto sysargs = Arguments::parse_from_string(input);
		if (sysargs->argv[0] == string("exit"))
		{
			break;
		}
		auto commandCreator = find_command(sysargs->argv[0]);
		if (commandCreator)
		{
			auto command = commandCreator->creator();
			command->program = shared_from_this();
			command->execute();
		}
		else
		{
			std::cout << "Unknown command: \"" << sysargs->argv[0] << "\"\n";
		}
	}
}