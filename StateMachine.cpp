#include "StateMachine.h"

StateMachine::StateMachine() {}

void StateMachine::transition(shared_ptr<State> new_state)
{
	current_state = new_state;
	current_state->machine = std::shared_ptr<StateMachine>(this);
}