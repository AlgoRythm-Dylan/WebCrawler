#include "Argument.h"

Argument::Argument()
{
	required = false;
	value_required = true;
	type = ArgumentType::Positional;
}

shared_ptr<Argument> Argument::flag()
{
	auto arg = std::make_shared<Argument>();
	arg->type == ArgumentType::Flag;
	return arg;
}

shared_ptr<Argument> Argument::key_value()
{
	auto arg = std::make_shared<Argument>();
	arg->type == ArgumentType::KeyValue;
	return arg;
}