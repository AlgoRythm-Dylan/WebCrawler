#include "AppArguments.h"

AppArguments::AppArguments()
{
	url = shared_ptr<Argument>(Argument::key_value("url"));
	same_site_flag = shared_ptr<Argument>(Argument::flag("same-site"));

	args.add_argument(url);
}

void AppArguments::parse(int argc, const char* argv[])
{
	args.parse(argc, argv);
}