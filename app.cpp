#include <iostream>
#include <fstream>

#include <URL.h>
#include <HTMLDocument.h>
#include <HTMLNode.h>
#include "AnsiColors.hpp"
#include "Helpers.h"
#include "CrawlJob.h"
#include <HttpClient.h>

using std::ifstream;

void url_mode();
void html_mode();
void crawl_mode();

int main(int argc, char* argv[])
{
	ansicolor::setup_ansi_mode();
	// Simple way to switch between the manual
	// testing modes. Certainly not production code.
	// The app project (WebCrawler) will significantly
	// increase in complexity once the tools are
	// complete (URL and HTML parsers, http client)
	
	//url_mode();
	//html_mode();
	crawl_mode();

	return 0;
}

void url_mode()
{
	string url_str;
	std::cout << "Please type any URL: " << ansicolor::yellow;
	std::getline(std::cin, url_str);
	std::cout << ansicolor::reset;

	Url url(url_str);

	if (url.is_valid)
	{
		std::cout << "\nHere is how your URL was parsed:\n";
		pretty_print_url(url);
		std::cout << "\n\n";
		print_url_details(url);
	}
	else
	{
		std::cout << ansicolor::red << "The provided URL is not valid (\"" << url_str << "\")" << ansicolor::reset;
	}

	std::cout << "\n";
}

void html_mode()
{
	//ifstream source("HTMLFiles\\text-node-only.html");
	ifstream source("HTMLFiles\\simple-with-comment.html");
	if (!source.is_open())
	{
		std::cout << "The document is not open" << std::endl;
	}
	else
	{
		HTMLDocument doc;
		doc.parse(source);
		pretty_print_document(doc);
	}
}

void crawl_mode()
{
	CrawlJob job;
	std::cout << "Input a URL: ";
	std::cin >> job.url;
	job.perform();
	std::cout << "Server responded with code ";
	if (job.response->status < 400)
	{
		std::cout << ansicolor::green;
	}
	else
	{
		std::cout << ansicolor::red;
	}
	std::cout << job.response->status << ansicolor::reset << "\n";
	pretty_print_document(job.document);
}