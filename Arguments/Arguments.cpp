#include "Arguments.h"

#include <iostream>

Arguments::Arguments()
{
	fail_on_unknown_flag = false;
	fail_on_duplicate_value = false;
}

void Arguments::add_argument(shared_ptr<Argument> arg)
{
	// TODO: validate
	args.push_back(arg);
}

shared_ptr<Argument> Arguments::find_flag(string_view name)
{
	char singleCharFlag = '\0';
	if (name.length() == 1)
	{
		singleCharFlag = name[0];
	}
	for (auto& arg : args)
	{
		if (arg->type == ArgumentType::Flag)
		{
			if (singleCharFlag != '\0')
			{
				for (auto& val : arg->short_flags)
				{
					if (val == singleCharFlag)
					{
						return arg;
					}
				}
			}
			else
			{
				for (auto& val : arg->long_flags)
				{
					if (val == name)
					{
						return arg;
					}
				}
			}
		}
	}
	return nullptr;
}

shared_ptr<Argument> Arguments::find_kv(string_view name)
{
	for (auto& arg : args)
	{
		if (arg->type == ArgumentType::KeyValue || arg->type == ArgumentType::KeyValueList)
		{
			for (auto& val : arg->long_flags)
			{
				if (val == name)
				{
					return arg;
				}
			}
		}
	}
	return nullptr;
}

void Arguments::parse(int argc, const char* argv[])
{

	shared_ptr<Argument> nextArg = nullptr;
	bool nextIsValue = false;

	for (int i = 1; i < argc; i++)
	{
		string sarg = argv[i];

		if (nextIsValue)
		{
			if (nextArg->type == ArgumentType::KeyValue)
			{
				nextArg->value = sarg;
			}
			else
			{
				nextArg->values.push_back(sarg);
			}
			nextIsValue = false;
			continue;
		}

		if (sarg.starts_with("--"))
		{
			string key_name = sarg.substr(2);
			if (key_name.empty())
			{
				// Empty "--" will just be treated as positional arg
				positionals.push_back(sarg);
				continue;
			}
			// KV or long flag
			auto arg = find_kv(key_name);
			if (arg)
			{
				// KV
				if (fail_on_duplicate_value && !arg->value.empty())
				{
					throw "Duplicate key/value: \"" + key_name + "\"";
				}
				else
				{
					nextArg = arg;
					nextIsValue = true;
				}
			}
			else
			{
				arg = find_flag(key_name);
				// long flag, if not null
				if (arg)
				{
					arg->is_set = true;
				}
				else
				{
					if (fail_on_unknown_flag)
					{
						throw "Unknown flag: \"" + sarg + "\"\n";
					}
				}
			}
		}
		// TODO: handle short flags for kv, kv_list types
		else if (sarg.starts_with("-"))
		{
			// Short flags
			if (sarg.size() == 1)
			{
				// "-" will be treated as positional
				positionals.push_back(sarg);
				continue;
			}
			for (int cursor = 1; cursor < sarg.size(); cursor++)
			{
				string flag = sarg.substr(cursor, 1);
				auto arg = find_flag(flag);
				if (arg)
				{
					arg->is_set = true;
				}
				else
				{
					arg = find_kv(flag);
					if (arg)
					{
						nextIsValue = true;
						nextArg = arg;
					}
					else
					{
						if (fail_on_unknown_flag)
						{
							throw "Unknown flag: \"" + flag + "\" in argument \"" + sarg + "\"";
						}
					}
				}
			}
		}
		else
		{
			// Positional
			positionals.push_back(sarg);
		}
	}
}