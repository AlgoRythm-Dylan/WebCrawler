#include "WebCrawler.h"

#include <iostream>

#include <AnsiColors.h>
#include <PrettyPrinting.h>

#include "Info.h"
#include "CrawlJob.h"

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
	inspect_interactive();
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

void WebCrawler::inspect_interactive()
{
	CrawlJob job;
	if (args.url->value.empty())
	{
		std::cout << "Enter URL: ";
		std::cin >> job.url;
	}
	else
	{
		job.url = args.url->value;
	}
	job.perform();
	std::cout << "Return code: ";
	if (colors())
	{
		std::cout << ansicolor::magenta;
	}
	std::cout << job.response->status << "\n";
	if (colors())
	{
		std::cout << ansicolor::reset;
	}
	std::cout << "Headers (" << job.response->headers.size() << "):\n";
	for (const auto& header : job.response->headers)
	{
		if (header.second.empty())
		{
			std::cout << "\t" << header.first << "\n";
		}
		else
		{
			std::cout << "\t" << header.first << ": " << header.second << "\n";
		}
	}
	if (job.response->status < 299)
	{
		pretty_print_document(job.document);
	}
}