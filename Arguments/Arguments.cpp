#include "Arguments.h"

Arguments::Arguments()
{
	fail_on_unknown_flag = false;
}

void Arguments::add_argument(shared_ptr<Argument> arg)
{
	// TODO: validate
	args.push_back(arg);
}

bool Arguments::flag_is_set(string_view flag)
{
	return false;
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
		if (arg->type == ArgumentType::KeyValue)
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
	flags.clear();
	kv_args.clear();
	positionals.clear();

	string key;
	bool nextIsValue = false;

	for (int i = 1; i < argc; i++)
	{
		string sarg = argv[i];
		if (sarg.starts_with("--"))
		{
			string key = sarg.substr(2);
			if (key.empty())
			{
				continue;
			}
			// KV or long flag
			auto arg = find_kv(key);
		}
		else if (sarg.starts_with("-"))
		{
			// Short flags
		}
		else
		{
			// Positional
		}
	}




















	/*bool nextIsValue = false;
	string key;
	for (int i = 1; i < argc; i++)
	{
		string sarg = string(argv[i]);
		if (nextIsValue)
		{
			kv_args.emplace(key, sarg);
			nextIsValue = false;
		}
		else
		{
			if (sarg.starts_with("-"))
			{
				if (sarg.starts_with("--"))
				{
					if (sarg.size() > 2)
					{
						nextIsValue = true;
						key = sarg.substr(2);
					}
				}
				else
				{
					for (int i = 1; i < sarg.size(); i++)
					{
						flags.insert(sarg[i]);
					}
				}
			}
			else
			{
				positionals.push_back(sarg);
			}
		}
	}*/
}