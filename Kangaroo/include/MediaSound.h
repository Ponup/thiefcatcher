#pragma once

#include <SDL3_mixer/SDL_mixer.h>

class MediaSound {
	
private:
	MIX_Audio *sound;
	
public:
	MediaSound();
	MediaSound( const char *name );
	~MediaSound();
	
	void load( const char *name );
	void play();
	void setVolume( int volume );
	MIX_Audio* toSDL();
};

