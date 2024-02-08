#include "HeadersInteractiveCommand.h"

#include <iostream>

#include <AnsiColors.h>

#include "InteractiveCrawl.h"

void HeadersInteractiveCommand::execute()
{
	auto programPtr = program.lock();
	auto appPtr = programPtr->app.lock();

	auto& headers = programPtr->current_job->response->headers;
	auto colors = appPtr->colors;
	if (headers.empty())
	{
		std::cout << "Server did not return any headers\n";
	}
	else
	{
		std::cout << "Server returned ";
		if (colors)
		{
			std::cout << ansicolor::yellow;
		}
		std::cout << headers.size();
		if (colors)
		{
			std::cout << ansicolor::reset;
		}
		std::cout << " headers\n";
		for (auto const& header : headers)
		{
			if (header.second.empty())
			{
				continue;
			}
			std::cout << "\t";
			if (colors)
			{
				std::cout << ansicolor::green;
			}
			std::cout << header.first;
			if (colors)
			{
				std::cout << ansicolor::reset;
			}
			std::cout << ": " << header.second << "\n";
		}
	}
}