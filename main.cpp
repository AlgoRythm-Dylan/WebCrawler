#include <iostream>

#include <URL.h>
#include <Ansicolors.h>

#include "WebCrawler.h"

int main(int argc, const char* argv[])
{
	ansicolor::setup_ansi_mode();

#if _DEBUG
	std::cout << "\n\tWarning: THIS IS A " << ansicolor::cyan << "DEBUG" << ansicolor::reset
		<< " BUILD! Performance may be subpar compared to a release build.\n\n";
#endif

	WebCrawler app;
	app.args.parse(argc, argv);

	app.start();

	return 0;
}
