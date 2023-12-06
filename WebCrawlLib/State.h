#pragma once

class StateMachine;

#include <memory>
#include <string>

using std::weak_ptr;
using std::shared_ptr;
using std::string;

class State
{
public:
	weak_ptr<StateMachine> machine;
	string name;
	void transition(shared_ptr<State>);
};

