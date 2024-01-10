#include "AppArguments.h"

AppArguments::AppArguments()
{
	url = shared_ptr<Argument>(Argument::key_value("url"));
	rules_list = shared_ptr<Argument>(Argument::key_value_list("rule"));
	no_banner_flag = shared_ptr<Argument>(Argument::flag("no-banner"));
	no_summary_flag = shared_ptr<Argument>(Argument::flag("no-summary"));
	no_color_flag = shared_ptr<Argument>(Argument::flag("no-color"));

	args.add_argument(url);
	args.add_argument(rules_list);
	args.add_argument(no_banner_flag);
	args.add_argument(no_summary_flag);
	args.add_argument(no_color_flag);
}

void AppArguments::parse(int argc, const char* argv[])
{
	args.parse(argc, argv);
}