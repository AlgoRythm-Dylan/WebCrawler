#pragma once

#include <string>
#include <set>

#include <HTMLDocument.h>
#include <HttpResponse.h>

using std::string;
using std::set;

class CrawlJob
{
public:
	string url, user_agent;
	HTMLDocument document;
	shared_ptr<HttpResponse> response;
	set<string> links_found;
	void perform();
	void find_links();
};
