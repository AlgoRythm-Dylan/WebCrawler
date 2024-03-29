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
Working: ANSI terminal colors library, URL parser, argument parser
In development: HTML parser, state machine framework
Prototype: WebCrawler client
Planned: JSON parser, XML parser
```

Plus, a unit testing project!

## WebCrawler client
This project includes the source code for an executable
which is intended to be an all-purpose web crawling/
scraping tool. The client application will have features
that are designed to work interactively with the user,
or to run as part of an automated/ scheduled job.

### Rules
Rules are set by the `--rule` command line argument and
dictate how the crawler behaves. This argument is a `list`
type, so you supply mulple values to it by passing it
to the program multiple times.

```sh
WebCrawlwer --rule SECURE-ONLY --rule IGNORE-NO-INDEX
```

The above command sets two rules: `SECURE-ONLY` and `IGNORE-NO-INDEX`

Current available rules:
- *(There are no currently implemented rules)*

### Options
```
[flag]    --no-banner: don't display banner on startup
[flag]    --no-color: don't use colors on output
[flag]    --no-summary: don't summarize the params of a job before it's executed
[key/val] --url: the (initial) URL to crawl
[key/val] --user-agent: User agent to use. Default is:
              WebCrawler by Dylan (https://github.com/AlgoRythm-Dylan/WebCrawler)
[list]    --rule: set a crawling rule
```

### Modes

Interactive mode (single-page inspect mode) puts you in
the driver's seat, crawling pages one-at-a-time.

Currently this is the only available mode, but in the
future this mode will need to be invoked with flag
`--mode=interactive`.

In this mode, you have a few commands you can interact
with.

```
crawl        Change the current page URL and re-crawl
headers      View headers from the most recent crawl
print        Display the content of the current page
stats        Display the stats of the current page
```

### Status:

*Implemented*:
- Argument parsing

*Prototype*:
- Single-page inspect mode

*Planned*:
- Database connection (+ in-memory and on-disk options)
- Automatic modes
- Multi-threaded modes
- Download-site mode
- Search modes
- HTML validation (missing closing tag, mismatched closing tag, etc)

*Ideas:*
- Lua scripting integration

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
- Attributes
- Self-closing tags
- Doctype declarations
- A rich DOM
- Comments
- `script` tags*
- Extranenous closing tags for self-closing elements
- Missing closing tags

*Prototype:*
- DOM querying (`document.querySelector[All]`)

*Planned:*
- `data:xyz` handling
- `pre` tags
- `style` tags*2
- HTML encoding / decoding

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

## Argument Parser
The argument parser is not extremely robust, but
certainly gets the job done. It supports four types
of argument:

- Positional
- Flag
- Key/Value
- Key/Value List

`Positional` arguments are areguments that start with
neither "--" nor "-". They are placed into a list in the
order  that the shell gives them to the program.

```sh
WebCrawler positional1 positional2
```

`Flag` arguments are arguments that start with "--" or
"-" and are not given any value. Their presence or absence
is the only important factor. Flags starting with "-" are
"short flags" - one character each. Short flags can be passed
more than one at a time in the format `-abc` (this sets the
flags `a`, `b`, and `c` all at once). Long flags are more
human-readable and are only sets one at a time such as
`--abc`, which sets the single `abc` flag.

```sh
WebCrawler --set-flag -flags
```

`Key/Value` arguments are similar to flags, but expect a
value. This value can either be the next argument, or
can be set using the format `--key=value`.

```sh
WebCrawler --url=https://www.google.com/search --user-agent "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36"
```

`Key/Value List` arguments are similar to key/value arguments,
but they can be set multiple times and their values are added
to a list

```sh
WebCrawler --header "User-Agent: xyz" --header "Accept: application/json"
```

## WebCrawler client changelog
```
0.1.7
- InteractiveCrawl now looks for both "location" and "Location"
0.1.6
- InteractiveCommand now parses command line arguments
- crawl command now properly accepts a url as its first
  positional argument
0.1.5
- Parser predictably handles mismatched end tags
0.1.4
- Add curl error handling, error message reporting, and interactive
  commands that require success from the previous crawl job
0.1.3
- Fix issue caused by wrong pointer to current node in HTML parser
0.1.2
- Fix massive memory leak regarding Token class without virtual destructor
0.1.1
- Added stats interactive command
0.1.0
- You can now use the program as an interactive crawler!
- Interactive mode asks to redirect when 3xx status returned
- Added crawl, print, and headers command
0.0.5
- Support for setting user agent. Default value provided
0.0.4
- Crawler now downloads and parses headers
0.0.3
- attributes are parsed with more accuracy.
  (No longer tricked by a dash in the name)
+ added unit tests for HTML attributes
0.0.2
- <script> tags are now handled properly
0.0.1
- Initial release!
```