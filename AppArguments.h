#pragma once

#include <memory>

#include "Arguments.h"

using std::shared_ptr;

class AppArguments
{
public:
	shared_ptr<Argument> url, same_site_flag;
	Arguments args;

	AppArguments();
	void parse(int, const char* []);
};

