#pragma once

#include <string>

using std::string;

class Token
{
public:
	string type;
};

namespace StdTokenType
{
	const static string end = "EOF";
	const static string str = "STR";
	const static string punctuation = "PUNCT";
}