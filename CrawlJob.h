#pragma once

#include <string>
#include <vector>

#include <HTMLDocument.h>
#include <HttpResponse.h>

using std::string;
using std::vector;

class CrawlJob
{
public:
	string url;
	HTMLDocument document;
	shared_ptr<HttpResponse> response;
	vector<string> links_found;
	void perform();
	void find_links();
};
