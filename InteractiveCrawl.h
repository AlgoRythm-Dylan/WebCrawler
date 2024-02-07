#pragma once

#include "CrawlJob.h"
#include "Program.h"

class InteractiveCrawl : public Program
{
protected:
	CrawlJob current_job;
	void query_url();
	void do_job();
	void prompt_user();
public:
	void execute() override;
};

