#include "StringMemoryLexingState.h"

#include "TokenBufferedLexer.h"

void StringMemoryLexingState::emit_memory()
{
	auto lexer = dynamic_cast<TokenBufferedLexer*>(machine);
	if (!memory.empty())
	{
		lexer->add_token<StringToken>(memory);
	}
}