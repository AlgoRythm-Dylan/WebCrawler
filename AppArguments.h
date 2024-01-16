#pragma once

#include <memory>

#include "Arguments.h"

using std::shared_ptr;

class AppArguments
{
public:
	shared_ptr<Argument> url, no_banner_flag, no_summary_flag, rules_list,
		no_color_flag, user_agent;
	Arguments args;

	AppArguments();
	void parse(int, const char* []);
};

