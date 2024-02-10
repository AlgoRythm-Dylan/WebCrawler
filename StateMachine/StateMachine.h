#pragma once

#include <memory>
#include "State.h"

using std::shared_ptr;

class StateMachine
{
public:
	shared_ptr<State> current_state;
	virtual void transition(shared_ptr<State>);

	StateMachine();
	virtual ~StateMachine();
};

