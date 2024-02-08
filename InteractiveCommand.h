#pragma once

#include <memory>

#include <Arguments.h>

class InteractiveCrawl;

using std::shared_ptr;

class InteractiveCommand
{
public:
	std::shared_ptr<InteractiveCrawl> program;
	Arguments args;
	virtual void execute() = 0;
};

#include "InteractiveCrawl.h"
