#include "HttpResponse.h"

HttpResponse::HttpResponse()
{
	response_size = 0;
	status = 0; // Not fetched / error
}

bool HttpResponse::is_success_status_code()
{
	return status <= 399;
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