#pragma once

#include <string>

using std::string;
using std::string_view;

class ParserMessage
{
public:
	int line, col;
	string category, message;

	ParserMessage();
	ParserMessage(string_view);
	ParserMessage(string_view, string_view);
	ParserMessage(string_view, string_view, int, int);
};
