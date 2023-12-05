#include "pch.h"
#include "StateMachine.h"

StateMachine::StateMachine() {}

void StateMachine::transition_to(shared_ptr<State> new_state)
{
	current_state = new_state;
	//current_state->machine = std::make_shared<StateMachine>(this);
}