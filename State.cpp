#include "State.h"

#include "StateMachine.h"

void State::transition(shared_ptr<State> state)
{
	machine->transition(state);
}