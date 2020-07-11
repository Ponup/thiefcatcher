#include "Updater.h"

#include <iostream>

#include <string.h>
using std::string;

const char Updater::GAME_VERSION_URL[] = "https://gist.githubusercontent.com/santiagolizardo/3751eace72f2b4423c4e1c94ed3bf729/raw/1b8443a546f553270ff2ae2000e77947107045a9/thiefcatcher-version.html";

CURL * Updater::handle = nullptr;

static int writeData(char *buffer, size_t size, size_t nmemb, string *content) {
	int length = 0;

	if (content != NULL) {
		length = size * nmemb;
		content->append(buffer, length);
	}

	return length;
}

optional<float> Updater::fetchNewVersionAvailable(const char *currentVersion) {
	optional<float> newVersion;

	const float clientVersion = std::stof(currentVersion);
	float serverVersion = 0.0f;

	curl_global_init(CURL_GLOBAL_ALL);
	handle = curl_easy_init();
	if (handle == NULL) {
		return false;
	}

	curl_easy_setopt(
			handle,
			CURLOPT_USERAGENT,
			"Mozilla/5.0 (Windows; U; Windows NT 5.1; es-ES; rv:1.8.0.3) Gecko/20060426 Firefox 2.0.0.6");
	curl_easy_setopt(handle, CURLOPT_URL, GAME_VERSION_URL);

	string content;
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, writeData);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, &content);
	curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, 2);

	CURLcode returnCode = curl_easy_perform(handle);
	if (returnCode != CURLE_OK) {
		fprintf(stderr, "Error: %s\n", curl_easy_strerror(returnCode));
	} else {
		long httpResponseCode;
		if (CURLE_OK == curl_easy_getinfo(handle, CURLINFO_HTTP_CODE, &httpResponseCode) ) {
			if (httpResponseCode == 200) {
				serverVersion = std::stof(content.c_str());
				if(serverVersion > clientVersion) {
					newVersion = serverVersion;
				}
			}
		}
	}

	curl_easy_cleanup(handle);
	curl_global_cleanup() ;

	return newVersion;
}
