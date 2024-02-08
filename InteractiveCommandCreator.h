#pragma once

#include <functional>
#include <memory>
#include <string>

#include "InteractiveCommand.h"

using std::function;
using std::shared_ptr;
using std::string;

class InteractiveCommandCreator
{
public:
	function<shared_ptr<InteractiveCommand>()> creator;
	string name, description;
	vector<string> aliases;
};

