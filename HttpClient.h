#pragma once

#include <curl/curl.h>
#include <string>

using std::string;

class HttpClient
{
protected:
	CURL* curl;
public:
	HttpClient();
	~HttpClient();

	string get_string(string);
};

