#include "pch.h"
#include "State.h"

#include "StateMachine.h"

void State::transition(shared_ptr<State> state)
{
	auto ptr = machine.lock();
	ptr->transition(state);
}