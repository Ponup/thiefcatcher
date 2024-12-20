#include "MediaManager.h"

#include <string>
using std::string;

MediaManager * MediaManager::singleton = NULL;
map<const char *, MediaSound *> MediaManager::sounds;

MediaManager &MediaManager::getInstance() {
	if(!singleton) {
		singleton = new MediaManager();
	}
	
	return *singleton;
}
		
void MediaManager::playSound(const char *name) {
	SoundsMap::const_iterator it;
	it = sounds.find(name);
	if(it == sounds.end()) {
		string mediaPath = "resources/sounds/" + string( name );
		MediaSound *mediaSound = new MediaSound( mediaPath.c_str() );
		mediaSound->play();

		sounds[name] = mediaSound;
	} else {
		MediaSound *mediaSound = it->second;
		mediaSound->play();
	}
}
