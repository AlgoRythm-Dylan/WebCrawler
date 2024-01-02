#pragma once

#include <string>

using std::string;

class HttpResponse
{
public:
	int status;
	string content_type;

	HttpResponse();
};

