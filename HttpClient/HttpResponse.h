#pragma once

#include <string>
#include <vector>
#include <utility>
#include <string_view>

#include <curl/curl.h>

using std::string;
using std::string_view;
using std::vector;
using std::pair;

class HttpResponse
{
public:
	int status;
	CURLcode curl_code;
	string content_type, error_message;
	size_t response_size;
	vector<pair<string, string>> headers;

	HttpResponse();

	bool has_curl_error();
	bool is_success_status_code();
	bool was_success();
	vector<pair<string, string>> search_headers(string_view);
};

