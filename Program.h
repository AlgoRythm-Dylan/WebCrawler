#pragma once

#include <string>
#include <memory>

class WebCrawler;

using std::string;
using std::shared_ptr;

struct Program
{
	string name, description;
	shared_ptr<WebCrawler> app;
	virtual void execute() = 0;
};

#include "WebCrawler.h"