#include "State.h"

#include "StateMachine.h"

State::State()
{
	machine = nullptr;
}

void State::transition(shared_ptr<State> state)
{
	machine->transition(state);
}

void State::transition(State* state)
{
	machine->transition(shared_ptr<State>(state));
}