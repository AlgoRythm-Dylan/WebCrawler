#include "WebCrawler.h"

#include <iostream>

#include <AnsiColors.h>
#include <PrettyPrinting.h>

#include "Info.h"
#include "CrawlJob.h"
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
	// For now. In future, find a way to wire up the correct program
	// based on the "mode" argument.
	auto interactiveCrawl = std::make_shared<InteractiveCrawl>();
	interactiveCrawl->app = shared_from_this();
	interactiveCrawl->execute();
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

/*void WebCrawler::inspect_interactive()
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
	if (!args.user_agent->value.empty())
	{
		job.user_agent = args.user_agent->value;
	}
	else
	{
		job.user_agent = args.user_agent->default_value;
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
	if (!job.response->headers.empty())
	{
		std::cout << "Headers (" << job.response->headers.size() << "):\n";
		for (const auto& header : job.response->headers)
		{

			std::cout << "\t";
			if (colors())
			{
				std::cout << ansicolor::bold << ansicolor::green;
			}
			std::cout << header.first;
			if (colors())
			{
				std::cout << ansicolor::reset;
			}
			if (header.second.empty())
			{
				std::cout << "\n";
			}
			else
			{
				std::cout << ": " << header.second << "\n";
			}
		}
	}
	else
	{
		std::cout << "No headers from server\n";
	}
	if (job.response->status < 299)
	{
		pretty_print_document(job.document);
	}
}*/