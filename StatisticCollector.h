#pragma once

#include <memory>

#include "CrawlJob.h"

using std::shared_ptr;

class StatisticCollector
{
	virtual void analyze(shared_ptr<CrawlJob>) = 0;
};