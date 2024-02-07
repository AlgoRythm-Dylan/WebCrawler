#include "WebCrawler.h"

#include <iostream>

#include <AnsiColors.h>

#include "Info.h"
#include "InteractiveCrawl.h"

void WebCrawler::start()
{
	if (!args.no_banner_flag->is_set)
	{
		show_banner();
	}
	if (!args.no_summary_flag->is_set)
	{
		show_summary();
	}
	// Read from args into app variables
	if (args.url->is_set)
	{
		url = args.url->value;
	}
	if (args.user_agent->is_set)
	{
		user_agent = args.user_agent->value;
	}
	else
	{
		user_agent = args.user_agent->default_value;
	}
	colors = !args.no_color_flag->is_set;

	// For now. In future, find a way to wire up the correct program
	// based on the "mode" argument.
	auto interactiveCrawl = std::make_shared<InteractiveCrawl>();
	interactiveCrawl->app = shared_from_this();
	interactiveCrawl->execute();
}

void WebCrawler::show_banner()
{
	if (colors)
	{
		std::cout << ansicolor::cyan;
	}
	std::cout << "\n\tWebCrawler";
	if (colors)
	{
		std::cout << ansicolor::reset;
	}
	std::cout << " by Dylan\n";
	std::cout << "\tVersion " << APP_VERSION << "\n\n";
}

void WebCrawler::show_summary()
{
	if (!args.rules_list->values.empty())
	{
		std::cout << "Rules: \n";
		for (auto& rule : args.rules_list->values)
		{
			std::cout << "\t" << rule << "\n";
		}
	}
}