#include "HttpResponse.h"

#include <curl/curl.h>
#include <LexingTools.h>

HttpResponse::HttpResponse()
{
	response_size = 0;
	status = 0; // Not fetched / error
}

bool HttpResponse::is_success_status_code()
{
	return status <= 399;
}

bool HttpResponse::has_curl_error()
{
	return curl_code != CURLE_OK;
}

bool HttpResponse::was_success()
{
	return !has_curl_error() && is_success_status_code();
}

vector<pair<string, string>> HttpResponse::search_headers(string_view search)
{
	vector<pair<string, string>> results;
	for (auto const& header : headers)
	{
		if (search == header.first)
		{
			results.push_back(header);
		}
	}
	return results;
}

vector<pair<string, string>> HttpResponse::search_headers_insensitive(string_view search)
{
	vector<pair<string, string>> results;
	for (auto const& header : headers)
	{
		if (LexingTools::compare_case_insensitive(search, header.first))
		{
			results.push_back(header);
		}
	}
	return results;
}