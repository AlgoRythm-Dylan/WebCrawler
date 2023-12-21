#pragma once

#include "URL.h"

void pretty_print_url(const Url& url, bool colors = true);
void print_url_details(const Url& url, bool colors = true);
void print_str_with_label(const string& label, const string& text, bool colors = true);
void print_bool_with_label(const string& label, const bool value, bool colors = true);