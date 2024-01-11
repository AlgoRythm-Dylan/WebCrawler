#pragma once

#include "AppArguments.h"

class WebCrawler
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
