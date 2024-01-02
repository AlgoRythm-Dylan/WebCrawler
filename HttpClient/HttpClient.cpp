#include "HttpClient.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	// Re-interpret the user pointer as our data callback
	auto dataCallback = *reinterpret_cast<function<void(char*, size_t)>*>(userp);
	dataCallback((char*)contents, size*nmemb);
	return size * nmemb;
}

HttpResponse HttpClient::get(const string& url,
	function<void(char*, size_t)> dataCallback,
	function<void(const HttpResponse&)> finishCallback)
{
	HttpResponse response;

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &dataCallback);

	curl_easy_perform(curl);

	// TODO: read response data

	finishCallback(response);
	curl_easy_cleanup(curl);

	return response;
}


/*string get_string(const string& url)
{
	auto curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	string read_buffer;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return read_buffer;
}*/