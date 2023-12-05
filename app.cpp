#include <iostream>

#include "URL.h"
#include "AnsiColors.hpp"
#include "HttpClient.h"

using wcrawl::URL;

int main()
{
	ansicolor::setup_ansi_mode();

	std::cout << ansicolor::screen_test << std::endl;
	//Url url("https://www.google.com/search?q=abc123&lang=EN-US");
	return 0;
}