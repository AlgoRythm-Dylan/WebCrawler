#pragma once

#include <curl/curl.h>
#include <string>

using std::string;

class HttpClient
{
public:
	static string get_string(string);
};

