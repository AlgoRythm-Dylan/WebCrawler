#pragma once

#include <string>
#include <vector>

#pragma warning(push)
// Library is being used by the same compiler,
// so this warning message is not an issue
#pragma warning(disable: 4251)

using std::string;
using std::vector;

namespace wcrawl
{
	class __declspec(dllexport) URL
	{
	public:
		string protocol, username, password, host, path, query;
		vector<string> host_parts;
		int port;

		URL();
	};
}
#pragma warning(pop)
