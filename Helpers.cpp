#include <iostream>

#include "Helpers.h"
#include "AnsiColors.hpp"

void pretty_print_url(const URL& url, bool colors)
{
	if (url.protocol != "")
	{
		if (colors)
		{
			std::cout << ansicolor::magenta;
		}
		std::cout << url.protocol;
		if (colors)
		{
			std::cout << ansicolor::white;
		}
		std::cout << "://";
		if (colors)
		{
			std::cout << ansicolor::reset;
		}
	}
}