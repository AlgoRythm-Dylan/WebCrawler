#include "StateMachine.h"

StateMachine::StateMachine()
{
	current_state = std::shared_ptr<State>(nullptr);
}

void StateMachine::transition(shared_ptr<State> new_state)
{
	current_state = new_state;
	current_state->machine = this;
}