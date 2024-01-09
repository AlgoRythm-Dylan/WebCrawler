#include "AppArguments.h"

AppArguments::AppArguments()
{
	url = shared_ptr<Argument>(Argument::key_value("url"));
	same_site_flag = shared_ptr<Argument>(Argument::flag("same-site"));
	no_banner_flag = shared_ptr<Argument>(Argument::flag("no-banner"));
	no_summary_flag = shared_ptr<Argument>(Argument::flag("no-summary"));

	args.add_argument(url);
	args.add_argument(same_site_flag);
	args.add_argument(no_banner_flag);
	args.add_argument(no_summary_flag);
}

void AppArguments::parse(int argc, const char* argv[])
{
	args.parse(argc, argv);
}