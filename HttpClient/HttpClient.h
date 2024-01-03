#pragma once

#include <string>
#include <functional>
#include <memory>

#include <curl/curl.h>

#include "HttpResponse.h"

using std::string;
using std::function;
using std::shared_ptr;

/*

	This class is designed to work well with the use case:
	web scraping. Not necessarily to be a good HttpClient.

	The basic design is that data should be processed in
	chunks as they come in. After the chunk is read,
	it should be forgotten about so that particularly
	large pages don't eat all our memory.

	A stringstream doesn't have an EOF like other IO streams
	do, so the parser will need to be notified that the
	input has ended. Unfortunately this means not simply
	passing a stringstream to HTMLDocument.parse()

*/
class HttpClient
{
public:
	CURL* curl;

	shared_ptr<HttpResponse> get(const string& url,
		function<void(char*, size_t)> dataCallback,
		function<void(shared_ptr<HttpResponse>)> finishCallback);
};
