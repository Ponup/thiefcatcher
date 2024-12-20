#pragma once

#include <map>
using std::map;

#include "MediaSound.h"

class MediaManager {
	
private:
	typedef map<const char *, MediaSound *> SoundsMap;

	static MediaManager *singleton;
	static SoundsMap sounds;

public:
	static MediaManager &getInstance();

	void playSound(const char *name);
};

