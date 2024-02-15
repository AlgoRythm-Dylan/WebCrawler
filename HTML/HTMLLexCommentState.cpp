#include "HTMLLexCommentState.h"

#include <PunctuationToken.h>

#include "HTMLLexer.h"
#include "HTMLLexGenericState.h"

HTMLLexCommentState::HTMLLexCommentState()
{
	consecutive_dash_count = 0;
}

bool HTMLLexCommentState::scan(const char character)
{
	if (character == '-')
	{
		consecutive_dash_count++;
	}
	else
	{
		if (character == '>')
		{
			if (consecutive_dash_count >= 2)
			{
				if (consecutive_dash_count > 2)
				{
					memory += string(consecutive_dash_count - 2, '-');
				}
				emit_memory();

				// Emit two dashes and a close bracket
				auto dashTok1 = new PunctuationToken("-");
				auto dashTok2 = new PunctuationToken("-");
				auto bracketTok = new PunctuationToken(">");

				auto lexer = (HTMLLexer*)machine;
				lexer->token_buffer.push(unique_ptr<Token>(dashTok1));
				lexer->token_buffer.push(unique_ptr<Token>(dashTok2));
				lexer->token_buffer.push(unique_ptr<Token>(bracketTok));

				transition(new HTMLLexGenericState());
			}
			else
			{
				consecutive_dash_count = 0;
			}
		}
		else
		{
			if (consecutive_dash_count > 0)
			{
				memory += string(consecutive_dash_count, '-');
				consecutive_dash_count = 0;
			}
			memory += character;
		}
	}
	return true;
}