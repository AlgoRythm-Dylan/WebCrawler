#include <iostream>

#include <URL.h>
#include "AnsiColors.hpp"
#include "Helpers.h"
#include <HttpClient.h>

int main()
{
	ansicolor::setup_ansi_mode();

	std::cout << ansicolor::screen_test << std::endl;

	string url_str = "https://AzureDiamond:hunter2@bash.org/chat?topic=security";
	Url url(url_str);
	/*url.protocol = "https";
	url.username = "AzureDiamond";
	url.password = "hunter2";
	url.host = "bash.org";
	url.host_parts = { "bash", "org" };
	url.path = "/chat";
	url.query = "?topic=security";
	
	std::cout << "Testing URL pretty printing\n\t";*/

	pretty_print_url(url);

	std::cout << "\n";
	return 0;
}