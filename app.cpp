#include <iostream>

#include <URL.h>
#include "AnsiColors.hpp"
#include "Helpers.h"
#include <HttpClient.h>

int main()
{
	ansicolor::setup_ansi_mode();

	std::cout << ansicolor::screen_test << std::endl;

	string url_str = "https://www.dylan.com";//AzureDiamond:hunter2@bash.org/chat?topic=security";
	Url url(url_str);

	pretty_print_url(url);

	std::cout << "\n";
	return 0;
}