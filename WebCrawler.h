#pragma once

#include <memory>

#include "AppArguments.h"

class WebCrawler : std::enable_shared_from_this<WebCrawler>
{
protected:
	void show_banner();
	void show_summary();
	bool colors();
public:
	AppArguments args;

	void start();
	void inspect_interactive();
};
