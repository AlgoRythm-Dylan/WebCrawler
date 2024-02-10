#include "StatsInteractiveCommand.h"

#include <iostream>

#include <AnsiColors.h>

#include "InteractiveCrawl.h"

void StatsInteractiveCommand::execute()
{
	auto programPtr = program.lock();
	auto appPtr = programPtr->app.lock();

	std::cout << "Response size: ";
	if (appPtr->colors)
	{
		std::cout << ansicolor::magenta;
	}
	std::cout << programPtr->current_job->response->response_size;
	if (appPtr->colors)
	{
		std::cout << ansicolor::reset;
	}
	std::cout << " bytes\n";
}