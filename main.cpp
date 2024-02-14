#include <iostream>
#include <csignal>

#include <URL.h>
#include <Ansicolors.h>

#include "WebCrawler.h"

void signal_handler(int sig)
{
	std::cout << "Interrupt signal received - goodbye!\n";
	exit(sig);
}

int main(int argc, const char* argv[])
{
	ansicolor::setup_ansi_mode();

#if _DEBUG
	std::cout << "\n\tWarning: THIS IS A " << ansicolor::cyan << "DEBUG" << ansicolor::reset
		<< " BUILD! Performance may be subpar compared to a release build.\n\n";
#endif

	signal(SIGINT, signal_handler);

	auto app = std::make_shared<WebCrawler>();
	app->args.parse(argc, argv);

	app->start();

	return 0;
}
