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
			string keyName = sarg.substr(2);
			if (keyName.empty())
			{
				// Empty "--" will just be treated as positional arg
				positionals.push_back(sarg);
				continue;
			}
			// KV or long flag
			auto equalIndex = keyName.find("=");
			string value;
			if (equalIndex != -1)
			{
				value = keyName.substr(equalIndex + 1);
				keyName = keyName.substr(0, equalIndex);
			}
			auto arg = find_kv(keyName);
			if (arg)
			{
				// KV
				if (fail_on_duplicate_value && !arg->value.empty())
				{
					throw "Duplicate key/value: \"" + keyName + "\"";
				}
				else
				{
					if (equalIndex != -1)
					{
						if (arg->type == ArgumentType::KeyValue)
						{
							arg->value = value;
						}
						else
						{
							arg->values.push_back(value);
						}
					}
					else
					{
						nextArg = arg;
						nextIsValue = true;
					}
				}
			}
			else
			{
				arg = find_flag(keyName);
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

unique_ptr<SysArgStruct> Arguments::parse_from_string(string_view input)
{
	auto args = std::make_unique<SysArgStruct>();
	args->argc = 0;

	vector<string> argv;
	bool inString = false;
	string currentArg = "";
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ')
		{
			if (inString)
			{
				currentArg += input[i];
			}
			else
			{
				argv.push_back(currentArg);
				currentArg = "";
			}
		}
		else
		{
			if (input[i] == '"')
			{
				inString = !inString;
			}
			else
			{
				currentArg += input[i];
			}
		}
	}

	if (!currentArg.empty())
	{
		argv.push_back(currentArg);
	}

	args->argc = argv.size();
	args->argv = new const char*[argv.size()];

	for (auto i = 0; i < args->argc; i++)
	{
		args->argv[i] = _strdup(argv[i].c_str());
	}

	return args;
}