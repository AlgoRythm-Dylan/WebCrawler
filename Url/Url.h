#pragma once

/*

https://bob:bobby@www.lunatech.com:8080/file;p=1?q=2#third
\___/   \_/ \___/ \______________/ \__/\_______/ \_/ \___/
  |      |    |          |          |      | \_/  |    |
Scheme User Password    Host       Port  Path |   | Fragment
		\_____________________________/       | Query
					   |               Path parameter
				   Authority

 */

#include <string>
#include <vector>

using std::string;
using std::vector;

class Url
{
public:
	string protocol, username, password, host, path, query;
	vector<string> host_parts;
	int port;
	bool is_valid, is_relative, is_fully_qualified;

	Url();
	Url(string&);

	void parse(string&);
};
