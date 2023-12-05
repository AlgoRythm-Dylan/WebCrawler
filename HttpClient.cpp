#include "HttpClient.h"

#include <curl/curl.h>

HttpClient::HttpClient()
{
	curl = curl_easy_init();
}

HttpClient::~HttpClient()
{
	curl_easy_cleanup(curl);
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

string HttpClient::get_string(string url)
{
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	string read_buffer;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
	curl_easy_perform(curl);
	return read_buffer;
}