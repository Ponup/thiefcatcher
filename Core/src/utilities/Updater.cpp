#include "Updater.h"

#include <iostream>

#include "Constants.h"

#include <string.h>
using std::string;

CURL * Updater::handle= NULL;

Updater::Updater() {
}

Updater::~Updater() {
}

int writeData(char *buffer, size_t size, size_t nmemb, string *content) {
	int length = 0;

	if (content != NULL) {
		length = size * nmemb;
		content->append(buffer, length);
	}

	return length;
}

bool Updater::existsNewVersion(const char *currentVersion) {
	bool newVersion = false;

	float clientVersion = 0.0f;
	float serverVersion = 0.0f;
	sscanf(currentVersion, "%f", &clientVersion);

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
		newVersion = false;
	} else {
		int respCode;
		if (CURLE_OK
				== curl_easy_getinfo(handle, CURLINFO_HTTP_CODE, &respCode) ) {
			if (respCode == 200) {
				sscanf(content.c_str(), "%f", &serverVersion);
				newVersion = serverVersion > clientVersion;
			}
		}
	}

	curl_easy_cleanup(handle);
	curl_global_cleanup() ;

	return newVersion;
}

