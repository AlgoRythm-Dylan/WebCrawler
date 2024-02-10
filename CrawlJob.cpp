#include "CrawlJob.h"

#include <HttpClient.h>
#include <HTMLDocument.h>
#include <HTMLLexer.h>
#include <HTMLParser.h>
#include <EOFToken.h>

void CrawlJob::perform()
{
	HttpClient client;
	if (!user_agent.empty())
	{
		client.user_agent = user_agent;
	}

	HTMLParser parser(document);
	HTMLLexer lexer;
	size_t byteCount = 0;

	client.get(url,
		[&lexer, &parser, &byteCount](char* buffer, size_t count)
		{
			byteCount += count;
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
		[this, &parser, &byteCount](shared_ptr<HttpResponse> res)
		{
			// On data finish
			response = res;
			response->response_size = byteCount;
			auto eofTok = unique_ptr<Token>(new EOFToken());
			parser.scan(std::move(eofTok));
			find_links();
		});
}

void recursive_find_links(shared_ptr<HTMLNode> node, set<string>& results)
{
	if (node->attributes.contains("href"))
	{
		string result = node->attributes["href"];
		if (!result.empty() && !result.starts_with("#"))
		{
			results.insert(result);
		}
	}
	else if (node->attributes.contains("src"))
	{
		string result = node->attributes["src"];
		if (!result.empty() && !result.starts_with("#"))
		{
			results.insert(result);
		}
	}
	for (auto& child : node->children)
	{
		if (child->type == HTMLNodeType::Element)
		{
			recursive_find_links(child, results);
		}
	}
}

void CrawlJob::find_links()
{
	links_found.clear();
	recursive_find_links(document.root, links_found);
}