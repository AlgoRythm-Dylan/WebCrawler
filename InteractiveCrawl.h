#pragma once

#include <memory>

#include "CrawlJob.h"
#include "Program.h"
#include "InteractiveCommandCreator.h"

class InteractiveCrawl : public Program, public std::enable_shared_from_this<InteractiveCrawl>
{
protected:
	void query_url();
	void start_interactive_prompt();
	vector<shared_ptr<InteractiveCommandCreator>> commands;
	shared_ptr<InteractiveCommandCreator> find_command(string_view);
public:
	unique_ptr<CrawlJob> current_job;

	InteractiveCrawl();

	void execute() override;
	void start_job();
	void do_job();
};

