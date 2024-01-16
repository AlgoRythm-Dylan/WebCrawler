#include "ParserMessage.h"

ParserMessage::ParserMessage()
{
	line = -1;
	col = -1;
}

ParserMessage::ParserMessage(string_view msg)
{
	line = -1;
	col = -1;
	message = msg;
}

ParserMessage::ParserMessage(string_view cat, string_view msg)
{
	line = -1;
	col = -1;
	message = msg;
	category = cat;
}

ParserMessage::ParserMessage(string_view cat, string_view msg, int ln, int c)
{
	line = ln;
	col = c;
	message = msg;
	category = cat;
}