#pragma once

#include <URL.h>
#include <HTMLDocument.h>

void pretty_print_url(const Url& url, bool colors = true);
void print_url_details(const Url& url, bool colors = true);
void print_str_with_label(const string& label, const string& text, bool colors = true);
void print_bool_with_label(const string& label, const bool value, bool colors = true);

void pretty_print_document(const HTMLDocument& document, bool colors = true);
void pretty_print_html_node(const HTMLNode& node, int indent, bool recursive = true, bool colors = true);