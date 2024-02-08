#pragma once

#include <memory>

#include <Arguments.h>

class InteractiveCrawl;

using std::weak_ptr;

class InteractiveCommand
{
public:
	std::weak_ptr<InteractiveCrawl> program;
	Arguments args;
	virtual void execute() = 0;
};
