#include <iostream>

#include "Helpers.h"
#include "AnsiColors.hpp"

void pretty_print_url(const Url& url, bool colors)
{
	if (!url.protocol.empty())
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
	if (!url.username.empty() && !url.password.empty())
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
	if (!url.host_parts.empty())
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
		bool firstRun = true;
		for (auto& part : url.path_parts)
		{
			// These two paths are different:
			//     /home/index       "absolute-relative"
			//     home/index        "relative"
			//
			// Therefore, they must be pretty-printed as such
			if (firstRun)
			{
				if (url.path.starts_with("/"))
				{
					if (colors)
					{
						std::cout << ansicolor::reset;
					}
					std::cout << "/";
				}
			}
			else
			{
				if (colors)
				{
					std::cout << ansicolor::reset;
				}
				std::cout << "/";
			}
			firstRun = false;
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
	if (!url.fragment.empty())
	{
		if (colors)
		{
			std::cout << ansicolor::reset;
		}
		std::cout << "#";
		if (colors)
		{
			std::cout << ansicolor::yellow << ansicolor::bold;
		}
		std::cout << url.fragment;
		if (colors)
		{
			std::cout << ansicolor::reset;
		}
	}
}

void print_url_details(const Url& url, bool colors)
{
	std::cout << "Valid: ";
	if (!url.is_valid)
	{
		if (colors)
		{
			std::cout << ansicolor::red;
		}
		std::cout << "false\n";
		if (colors)
		{
			std::cout << ansicolor::reset;
		}
		return; // Invalid URLs shouldn't be printed
	}
	else
	{
		if (colors)
		{
			std::cout << ansicolor::green;
		}
		std::cout << "true";
		if (colors)
		{
			std::cout << ansicolor::reset;
		}
	}
	std::cout << "\nRelative/absolute: ";
	if (colors)
	{
		std::cout << ansicolor::yellow << ansicolor::bold;
	}
	if (url.is_relative)
	{
		std::cout << "relative";
	}
	else
	{
		std::cout << "absolute";
	}
	if (colors)
	{
		std::cout << ansicolor::reset;
	}
	print_str_with_label("\nProtocol: ", url.protocol);
	print_str_with_label("\nUsername: ", url.username);
	print_str_with_label("\nPassword: ", url.password);
	print_str_with_label("\nHost: ", url.host);
	print_str_with_label("\nPath: ", url.path);
	print_str_with_label("\nQuery: ", url.query);
	print_str_with_label("\nFragment: ", url.fragment);
}

void print_str_with_label(const string& label, const string& text, bool colors)
{
	std::cout << label;
	
	if (text.empty())
	{
		if (colors)
		{
			std::cout << ansicolor::dim;
		}
		std::cout << "<None>";
	}
	else
	{
		if (colors)
		{
			std::cout << ansicolor::yellow << ansicolor::bold;
		}
		std::cout << text;
	}
	if (colors)
	{
		std::cout << ansicolor::reset;
	}
}