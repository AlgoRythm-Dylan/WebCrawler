#include "HTMLLexScriptTagState.h"

#include <PunctuationToken.h>

#include "HTMLLexer.h"
#include "HTMLLexGenericState.h"

HTMLLexScriptTagState::HTMLLexScriptTagState() : end_tag_tracker("</script>") 
{
	end_tag_tracker.is_case_insensitive = true;
}

bool HTMLLexScriptTagState::scan(const char character)
{
	memory += character;
	end_tag_tracker.add(character);
	if (character == '>')
	{
		if (end_tag_tracker.is_match())
		{
			// Cut off the end of memory, then emit appropriate tokens
			// </script> is 9 chars
			memory = memory.substr(0, memory.size() - 9);
			emit_memory();

			auto openBracketPuncTok = new PunctuationToken("<");
			auto slashPuncTok = new PunctuationToken("/");
			auto scriptStringTok = new StringToken("script");
			auto closeBracketPuncTok = new PunctuationToken(">");

			auto lexer = (HTMLLexer*)machine;
			lexer->token_buffer.push(unique_ptr<Token>(openBracketPuncTok));
			lexer->token_buffer.push(unique_ptr<Token>(slashPuncTok));
			lexer->token_buffer.push(unique_ptr<Token>(scriptStringTok));
			lexer->token_buffer.push(unique_ptr<Token>(closeBracketPuncTok));

			// and transition state to generic state.
			transition(new HTMLLexGenericState());
		}
	}
	return true;
}