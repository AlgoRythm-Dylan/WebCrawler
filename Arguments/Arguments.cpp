#include "Arguments.h"

void Arguments::parse(int argc, const char* argv[])
{
	flags.clear();
	kv_args.clear();
	positionals.clear();

	bool nextIsValue = false;
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
	}
}