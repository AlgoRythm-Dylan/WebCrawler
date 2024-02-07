#pragma once

#include <memory>

#include "AppArguments.h"
#include "Program.h"

class WebCrawler : public std::enable_shared_from_this<WebCrawler>
{
protected:
	void show_banner();
	void show_summary();
	bool colors();
public:
	AppArguments args;
	shared_ptr<Program> current_program;

	void start();
};
