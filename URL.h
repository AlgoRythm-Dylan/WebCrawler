#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class URL
{
public:
	string protocol, username, password, host, path, query;
	vector<string> host_parts;
	int port;

	URL();
};
