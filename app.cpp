#include <iostream>

#include "URL.h"
#include "AnsiColors.hpp"
#include "HttpClient.h"

using wcrawl::URL;

void curl_test();

int main()
{

	ansicolor::setup_ansi_mode();

	std::cout << ansicolor::screen_test << std::endl;

	std::cout << "Testing curl..." << std::endl;
	curl_test();

	//Url url("https://www.google.com/search?q=abc123&lang=EN-US");
	return 0;
}

void curl_test()
{
	HttpClient client;
	string response = client.get_string("https://curl.se/libcurl/c/");
	std::cout << "=====================\n\n\t\tHTTP RESPONSE\n\n=====================\n\n";
	std::cout << response;
}