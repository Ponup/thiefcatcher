#pragma once

#include <curl/curl.h>

#include <optional>
using std::optional;

class Updater {

private:
	static CURL *handle;
	
public:
	static optional<float> fetchNewVersionAvailable(const char *currentVersion);
};
