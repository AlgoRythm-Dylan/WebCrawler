#include <iostream>

#include <URL.h>
#include "AnsiColors.hpp"
#include "Helpers.h"
#include <HttpClient.h>

int main()
{
	ansicolor::setup_ansi_mode();

	//std::cout << ansicolor::screen_test << std::endl;

	string url_str;// = "https://AzureDiamond:hunter2@bash.org";///chat?topic=security";
	//Url url(url_str);

	std::cout << "Please type any URL: " << ansicolor::yellow;
	std::getline(std::cin, url_str);
	std::cout << ansicolor::reset;

	Url url(url_str);

	if (url.is_valid)
	{
		std::cout << "\nHere is how your URL was parsed:\n";
		pretty_print_url(url);
	}
	else
	{
		std::cout << ansicolor::red << "The provided URL is not valid (\"" << url_str << "\")" << ansicolor::reset;
	}

	std::cout << "\n";
	return 0;
}