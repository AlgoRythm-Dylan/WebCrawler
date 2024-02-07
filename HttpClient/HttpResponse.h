#pragma once

#include <string>
#include <vector>
#include <utility>

using std::string;
using std::vector;
using std::pair;

class HttpResponse
{
public:
	int status;
	string content_type;
	size_t response_size;
	vector<pair<string, string>> headers;

	HttpResponse();

	bool is_success_status_code();
};

