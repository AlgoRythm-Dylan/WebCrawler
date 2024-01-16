#include "Lexer.h"

Lexer::Lexer()
{
	line = 0;
	col = 0;
	ch = 0;
}

void Lexer::update_position(const char character)
{
	ch++;
	if (character == '\n')
	{
		col = 0;
		line++;
	}
	else
	{
		col++;
	}
}