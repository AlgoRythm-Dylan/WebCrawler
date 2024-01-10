#include "WebCrawler.h"

#include <iostream>

#include <AnsiColors.h>

#include "Info.h"

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
}

void WebCrawler::show_banner()
{
	if (colors())
	{
		std::cout << ansicolor::cyan;
	}
	std::cout << "\n\tWebCrawler";
	if (colors())
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

bool WebCrawler::colors()
{
	return !args.no_color_flag->is_set;
}