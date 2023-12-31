#include <iostream>
#include <fstream>

#include <URL.h>
#include <HTMLDocument.h>
#include <HTMLNode.h>
#include "AnsiColors.hpp"
#include "Helpers.h"
#include <HttpClient.h>

using std::ifstream;

void url_mode();
void html_mode();

int main()
{
	ansicolor::setup_ansi_mode();
	// Simple way to switch between the manual
	// testing modes. Certainly not production code.
	// The app project (WebCrawler) will significantly
	// increase in complexity once the tools are
	// complete (URL and HTML parsers, http client)
	
	//url_mode();
	html_mode();

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
	ifstream source("HTMLFiles\\doctype-only.html");
	if (!source.is_open())
	{
		std::cout << "The document is not open" << std::endl;
	}
	else
	{
		HTMLDocument doc;
		doc.parse(source);
		pretty_print_document(doc);

		std::cout << "\n\n";

		/*HTMLDocument testDoc;
		auto el = std::make_shared<HTMLNode>();
		el->tag_name = "div";
		testDoc.children.push_back(el);
		auto elTextContent = std::make_shared<HTMLNode>();
		elTextContent->text_content = "This is the content of the div";
		el->children.push_back(elTextContent);
		pretty_print_document(testDoc);*/
	}
}