#pragma once

#include <queue>
#include <string_view>

#include "Lexer.h"
#include "StringToken.h"

using std::queue;
using std::string_view;

class TokenBufferedLexer : public Lexer
{
public:
	queue<unique_ptr<Token>> token_buffer;

	template<typename T, typename... Args>
	void add_token(Args&&... args)
	{
		static_assert(std::is_base_of<Token, T>::value, "Argument must be Token");
		token_buffer.push(unique_ptr<Token>(new T(std::forward<Args>(args)...)));
	}

	void punct(string_view);
	void str(string_view);
	void eof();
};
