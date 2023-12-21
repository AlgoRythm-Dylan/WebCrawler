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
Working: ANSI terminal colors library
In development: URL parser, state machine framework
Prototype:
Planned: HTML parser, JSON parser, XML parser
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