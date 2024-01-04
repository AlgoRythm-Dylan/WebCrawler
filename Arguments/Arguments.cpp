#include "Arguments.h"

void Arguments::parse(int argc, char* argv[])
{
	bool nextIsValue = false;
	string key;
	args.clear();
	for (int i = 1; i < argc; i++)
	{
		if (nextIsValue)
		{
			
		}
		string sarg = string(argv[i]);
		if (sarg.starts_with("-"))
		{
			if (sarg.starts_with("--"))
			{

			}
		}
		else
		{

		}
	}
}