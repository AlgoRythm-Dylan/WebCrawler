#pragma once

#include <string>

#include <HTMLDocument.h>
#include <HttpResponse.h>

using std::string;

class CrawlJob
{
public:
	string url;
	HTMLDocument document;
	shared_ptr<HttpResponse> response;
	void perform();
};
