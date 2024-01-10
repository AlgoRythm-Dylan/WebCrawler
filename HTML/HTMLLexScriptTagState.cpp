#include "HTMLLexScriptTagState.h"

HTMLLexScriptTagState::HTMLLexScriptTagState() : end_tag_tracker("</script>") 
{
	end_tag_tracker.is_case_insensitive = true;
}

LexingScanResult HTMLLexScriptTagState::scan(const char character)
{
	LexingScanResult result;
	memory += character;
	end_tag_tracker.add(character);
	if (character == '>')
	{
		if (end_tag_tracker.is_match())
		{
			// Cut off the end of memory, then emit appropriate tokens
			// and transition state to generic state.
		}
	}
	return result;
}