#pragma once

#include <string>
#include <memory>

class WebCrawler;

using std::string;
using std::weak_ptr;

struct Program
{
	string name, description;
	weak_ptr<WebCrawler> app;
	virtual void execute() = 0;
};

#include "WebCrawler.h"