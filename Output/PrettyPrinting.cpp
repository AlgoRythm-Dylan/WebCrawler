#include <iostream>

#include <HTMLNode.h>

#include "PrettyPrinting.h"
#include "AnsiColors.h"

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
		if (url.is_ipv6)
		{
			std::cout << "[";
		}
		for (int i = 0; i < url.host_parts.size(); i++)
		{
			if (colors)
			{
				std::cout << ansicolor::bold << ansicolor::green;
				if (url.is_ipv4)
				{
					std::cout << ansicolor::underline;
				}
			}
			std::cout << url.host_parts[i];
			if (colors)
			{
				std::cout << ansicolor::reset;
			}
			if (i != url.host_parts.size() - 1)
			{
				if (url.is_ipv6)
				{
					std::cout << ":";
				}
				else
				{
					std::cout << ".";
				}
			}
		}
		if (url.is_ipv6)
		{
			std::cout << "]";
		}
	}
	if (url.port != 0)
	{
		if (colors)
		{
			std::cout << ansicolor::reset;
		}
		std::cout << ":";
		if (colors)
		{
			std::cout << ansicolor::red << ansicolor::bold;
		}
		std::cout << url.port;
		if (colors)
		{
			std::cout << ansicolor::reset;
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
	print_bool_with_label("Valid: ", url.is_valid);
	if (!url.is_valid)
	{
		// Invalid URLs should not be printed
		return;
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
	if (url.port == 0)
	{
		print_str_with_label("\nPort: ", "");
	}
	else
	{
		print_str_with_label("\nPort: ", std::to_string(url.port));
	}
	print_str_with_label("\nPath: ", url.path);
	print_str_with_label("\nQuery: ", url.query);
	print_str_with_label("\nFragment: ", url.fragment);
	print_bool_with_label("\nIPv4: ", url.is_ipv4);
	print_bool_with_label("\nIPv6: ", url.is_ipv6);
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

void print_bool_with_label(const string& label, const bool value, bool colors)
{
	std::cout << label;
	if (value)
	{
		if (colors)
		{
			std::cout << ansicolor::green;
		}
		std::cout << "true";
	}
	else
	{
		if (colors)
		{
			std::cout << ansicolor::red;
		}
		std::cout << "false";
	}
	if (colors)
	{
		std::cout << ansicolor::reset;
	}
}

void pretty_print_document(const HTMLDocument& document, bool colors)
{
	for (auto& node : document.root->children)
	{
		pretty_print_html_node(*node, 0, true, colors);
	}
}

void pretty_print_html_node(const HTMLNode& node, int indent, bool recursive, bool colors)
{
	if (node.type == HTMLNodeType::Comment)
	{
		// Comments can't be formatted nicely
		// because whitespace is preserved.
		// So, just open the comment on one line,
		// then new line, then push the comment out,
		// then end it with closing comment
		std::cout << string(indent * 2, ' ');
		if (colors)
		{
			std::cout << ansicolor::green << ansicolor::bold;
		}
		std::cout << "<!--";
		string format;
		if (colors)
		{
			format = ansicolor::green + ansicolor::bold;
		}
		if (is_single_line(node.text_content))
		{
			std::cout << node.text_content;
		}
		else
		{
			std::cout << "\n";
			print_indented_text(node.text_content, format, indent);
			std::cout << string(indent * 2, ' ');
			if (colors)
			{
				std::cout << ansicolor::green << ansicolor::bold;
			}
		}
		std::cout << "-->";
		if (colors)
		{
			std::cout << ansicolor::reset;
		}
		std::cout << "\n";
	}
	else if (node.type == HTMLNodeType::Element)
	{
		std::cout << string(2 * indent, ' ') << "<";
		if (colors)
		{
			std::cout << ansicolor::bold << ansicolor::blue;
		}
		std::cout << node.tag_name;
		if (colors)
		{
			std::cout << ansicolor::reset;
		}
		// Print attributes. Will need to worry about multiline ones later
		for (auto const& x : node.attributes)
		{
			std::cout << " ";
			if (colors)
			{
				std::cout << ansicolor::bold << ansicolor::cyan;
			}
			std::cout << x.first;
			if (colors)
			{
				std::cout << ansicolor::reset;
			}
			if (!x.second.empty())
			{
				std::cout << "=\"" << x.second << "\"";
			}
		}
		std::cout << ">";
		if (!node.children.empty() || !recursive)
		{
			std::cout << "\n";
		}
		bool printedNewline = false;
		if (recursive && !node.is_void_element())
		{
			for (auto& child : node.children)
			{
				pretty_print_html_node(*child, indent + 1, colors);
			}
		}
		if (!node.is_void_element())
		{
			if (!node.children.empty())
			{
				std::cout << string(2 * indent, ' ');
			}
			std::cout << "</";
			if (colors)
			{
				std::cout << ansicolor::bold << ansicolor::blue;
			}
			std::cout << node.tag_name;
			if (colors)
			{
				std::cout << ansicolor::reset;
			}
			std::cout << ">";
		}
		std::cout << "\n";
	}
	else
	{
		// Simple text node
		string format;
		if (colors)
		{
			format = ansicolor::yellow + ansicolor::bold;
		}
		print_indented_text(node.text_content, format, indent);
	}
}

void print_indented_text(const string& text, const string& format, int indent)
{
	string currentLine;
	for (auto& character : text)
	{
		if (character == '\n')
		{
			if (!currentLine.empty())
			{
				std::cout << string(2 * indent, ' ');
				if (!format.empty())
				{
					std::cout << format;
				}
				std::cout << currentLine;
				if (!format.empty())
				{
					std::cout << ansicolor::reset;
				}
				std::cout << "\n";
				currentLine = "";
			}
		}
		else
		{
			if (character != '\r' && (character != ' ' || !currentLine.empty()))
			{
				currentLine += character;
			}
		}
	}
	if (!currentLine.empty())
	{
		std::cout << string(2 * indent, ' ');
		if (!format.empty())
		{
			std::cout << format;
		}
		std::cout << currentLine;
		if (!format.empty())
		{
			std::cout << ansicolor::reset;
		}
		std::cout << "\n";
	}
}

bool is_single_line(const string& text)
{
	for (auto& character : text)
	{
		if (character == '\n' || character == '\r')
		{
			return false;
		}
	}
	return true;
}