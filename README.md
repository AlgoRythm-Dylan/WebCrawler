# WebCrawler
This project is educational. The main goal
is to become familiar with c++, parsing/lexing,
state machines, and other technology. The
secondary goal is to make a neat little web
crawler/scraper.

The idea is to implement everything *practical*
by hand, especially core concepts of web scraping.

This means URL, HTML, JSON, and XML parsing -
maybe even CSS (JavaScript parsing might not
be practical though)

The project also focuses on functionality over
performance. If it runs, it runs. I surely
do not wish to abandon the project because I
spent too much time making an HTML document parse
in under 100ms.

## What do you have to show?

```
Working: ANSI terminal colors library, URL parser
In development: state machine framework
Prototype: HTML parser
Planned: JSON parser, XML parser
```

Plus, a unit testing project!

## URL parser
The URL parser is pretty robust at this point
and of course supports relative paths like you might
see in HTML pages, which would be invalid URLs on
their own.

Here is a complicated parse with just about
as many features as a URL can have, including
a properly detected IPv4 address:

![complex url parse](docs/complex%20url%20parse.jpg)

It can correctly identify relative paths:

![simple relative url parse](docs/simple%20relative%20parse.jpg)

Even just a query string is detected as a
valid relative path:

![complex relative url parse](docs/difficult%20relative%20parse.jpg)

The parser supports detecting IPv6, but does not
validate it as it does IPv4.

# HTML Parser
[Famously a job for a parser](https://stackoverflow.com/questions/1732348/regex-match-open-tags-except-xhtml-self-contained-tags/1732454?ref=blog.codinghorror.com#1732454),
this project aims to support:

*Implemented:*
- *(empty list)*

*Planned:*
- Doctype declarations
- HTML5 standard
- A rich DOM
- Comments
- Self-closing tags
- Extranenous closing tags for self-closing elements
- Missing closing tags
- Attributes
- `data:xyz` handling
- `pre` tags
- `script` tags*
- `style` tags*2
- HTML encoding / decoding
- DOM querying (`document.querySelector[All]`)

*NOT JS parsing. Some very basic parsing so
that `</script>` inside a string literal
isn't confused as the closing tag.

*2 Similar to script tags. Only enough to
not be tricked by a closing `</style>` inside
a string literal, but this is less of a concern
for CSS. Why would that be there? Who knows,
but I bet it does exist somewhere on the web for
some reason. Maybe in a `content` attribute.
However, in contrast to JS, I would actually
like to write a CSS3 parser.