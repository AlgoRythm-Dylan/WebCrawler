#pragma once

#include <string>

using std::string;

namespace wcrawl
{
	class __declspec(dllexport) URL
	{
	public:
		string protocol;
		int port;

		URL();
	};
}
