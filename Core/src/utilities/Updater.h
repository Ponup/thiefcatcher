#ifndef UPDATER_H_
#define UPDATER_H_

#include <curl/curl.h>

class Updater {

private:
	static CURL *handle;
	
public:
	Updater();
	virtual ~Updater();

	static bool existsNewVersion(const char *currentVersion);
};

#endif

