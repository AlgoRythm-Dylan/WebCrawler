#include "Argument.h"

Argument::Argument()
{
	required = false;
	value_required = true;
	is_set = false;
	type = ArgumentType::Positional;
}

shared_ptr<Argument> Argument::flag()
{
	auto arg = std::make_shared<Argument>();
	arg->type = ArgumentType::Flag;
	return arg;
}

shared_ptr<Argument> Argument::flag(char flag)
{
	auto arg = std::make_shared<Argument>();
	arg->type = ArgumentType::Flag;
	arg->short_flags.insert(flag);
	return arg;
}

shared_ptr<Argument> Argument::flag(string_view flag)
{
	auto arg = std::make_shared<Argument>();
	arg->type = ArgumentType::Flag;
	arg->long_flags.insert(string(flag));
	return arg;
}

shared_ptr<Argument> Argument::key_value()
{
	auto arg = std::make_shared<Argument>();
	arg->type = ArgumentType::KeyValue;
	return arg;
}

shared_ptr<Argument> Argument::key_value(string_view key)
{
	auto arg = std::make_shared<Argument>();
	arg->type = ArgumentType::KeyValue;
	arg->long_flags.insert(string(key));
	return arg;
}

shared_ptr<Argument> Argument::key_value_list()
{
	auto arg = std::make_shared<Argument>();
	arg->type = ArgumentType::KeyValueList;
	return arg;
}

shared_ptr<Argument> Argument::key_value_list(string_view key)
{
	auto arg = std::make_shared<Argument>();
	arg->type = ArgumentType::KeyValueList;
	arg->long_flags.insert(string(key));
	return arg;
}