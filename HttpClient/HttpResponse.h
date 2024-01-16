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
	vector<pair<string, string>> headers;

	HttpResponse();
};

