#include <iostream>

#include "Helpers.h"
#include "AnsiColors.hpp"

void pretty_print_url(const Url& url, bool colors)
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
	if (url.username != "" && url.password != "")
	{
		if (colors)
		{
			std::cout << ansicolor::cyan;
		}
		std::cout << url.username;
		if (colors)
		{
			std::cout << ansicolor::reset;
		}
		std::cout << ":";
		if (colors)
		{
			std::cout << ansicolor::cyan;
		}
		std::cout << url.password;
		if (colors)
		{
			std::cout << ansicolor::reset;
		}
		std::cout << "@";
	}
	if (url.host_parts.size() != 0)
	{
		for (int i = 0; i < url.host_parts.size(); i++)
		{
			if (colors)
			{
				std::cout << ansicolor::bold << ansicolor::green;
			}
			std::cout << url.host_parts[i];
			if (colors)
			{
				std::cout << ansicolor::reset;
			}
			if (i != url.host_parts.size() - 1)
			{
				std::cout << ".";
			}
		}
	}
	if (!url.path_parts.empty())
	{
		for (auto& part : url.path_parts)
		{
			if (colors)
			{
				std::cout << ansicolor::reset;
			}
			std::cout << "/";
			if (colors)
			{
				std::cout << ansicolor::bold << ansicolor::yellow;
			}
			std::cout << part;
			if (colors)
			{
				std::cout << ansicolor::reset;
			}
		}
	}
	if (!url.query_parts.empty())
	{
		for (int i = 0; i < url.query_parts.size(); i++)
		{

			if (colors)
			{
				std::cout << ansicolor::bold << ansicolor::magenta;
			}
			if (i == 0)
			{
				std::cout << "?";
			}
			else
			{
				std::cout << "&";
			}
			if (colors)
			{
				std::cout << ansicolor::reset << ansicolor::bold << ansicolor::blue;
			}
			std::cout << url.query_parts[i].key;
			if (!url.query_parts[i].value.empty())
			{
				if (colors)
				{
					std::cout << ansicolor::reset << ansicolor::dim;
				}
				std::cout << "=";
				if (colors)
				{
					std::cout << ansicolor::reset << ansicolor::cyan;
				}
				std::cout << url.query_parts[i].value;
				if (colors)
				{
					std::cout << ansicolor::reset;
				}
			}
		}
	}
}

void print_url_details(const Url& url, bool colors)
{

}