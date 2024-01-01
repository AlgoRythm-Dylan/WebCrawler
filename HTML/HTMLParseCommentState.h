#pragma once

#include <ParsingState.h>

class HTMLParseCommentState : public ParsingState
{
protected:
	int consecutive_dash_count;
public:
	HTMLParseCommentState();

	unique_ptr<Token> scan(unique_ptr<Token>) override;
};
