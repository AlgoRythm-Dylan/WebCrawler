#include "CrawlJob.h"

#include <HttpClient.h>
#include <HTMLDocument.h>
#include <HTMLLexer.h>
#include <HTMLParser.h>
#include <EOFToken.h>

#include "AnsiColors.hpp"

void CrawlJob::perform()
{
	HttpClient client;

	HTMLParser parser(document);
	HTMLLexer lexer;

	client.get(url,
		[&lexer, &parser](char* buffer, size_t count)
		{
			// On data get
			for (size_t i = 0; i < count; i++)
			{
				auto result = lexer.read(buffer[i]);
				while (!lexer.token_buffer.empty())
				{
					auto tok = std::move(lexer.token_buffer.front());
					lexer.token_buffer.pop();
					// Handle returned tokens
					while (tok)
					{
						tok = parser.scan(std::move(tok));
					}
				}
				// "putback" if not consumed
				if (!result.consumed)
				{
					i--;
				}
			}
		},
		[this, &parser](shared_ptr<HttpResponse> res)
		{
			// On data finish
			response = res;
			auto eofTok = unique_ptr<Token>(new EOFToken());
			parser.scan(std::move(eofTok));
		});
}