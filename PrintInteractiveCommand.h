#pragma once

#include "InteractiveCommand.h"

class PrintInteractiveCommand : public InteractiveCommand
{
public:
	void execute() override;
};

