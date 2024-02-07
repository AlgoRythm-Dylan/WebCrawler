#pragma once

#include <memory>
#include <string>
#include <optional>

#include "AppArguments.h"
#include "Program.h"

using std::string;
using std::optional;

class WebCrawler : public std::enable_shared_from_this<WebCrawler>
{
protected:
	void show_banner();
	void show_summary();
public:
	AppArguments args;
	shared_ptr<Program> current_program;

	std::optional<std::string> url, user_agent;
	std::set <std::string> rules;
	bool colors = false;

	void start();
};
