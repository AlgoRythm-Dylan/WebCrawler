#pragma once

/*

VALID URLs:
	https://abc123.edu/123  ("fully-qualified")
	/123 ("absolute-relative")
	123 ("relative")

INVALID URLs:
	localhost:8080/abc123
	bob:bobby@www.lunatech.com/test
 */

#include <string>
#include <vector>
#include <utility>

#include "UrlQueryEntry.h"

using std::string;
using std::vector;

class Url
{
protected:
	void setup_defaults();
public:
	string protocol, username, password, host, path, query, fragment;
	vector<string> host_parts, path_parts;
	vector<UrlQueryEntry> query_parts;
	int port;
	bool is_valid, is_relative, is_ipv4, is_ipv6;

	Url();
	Url(const string&);

	void parse(const string&);
};
