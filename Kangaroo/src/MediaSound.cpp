#include "MediaSound.h"

#include <stdexcept>

#include <SDL3/SDL.h>

MediaSound::MediaSound() {
	sound = nullptr;
}

MediaSound::MediaSound(const char *name) {
	load(name);
}

MediaSound::~MediaSound() {
	if(sound)
		MIX_DestroyAudio(sound);
}

void MediaSound::load(const char *name) {
	sound = MIX_LoadAudio(nullptr, name, true);
	if(!sound) {
		throw std::runtime_error(SDL_GetError());
	}
}

void MediaSound::play() {
	if (sound) {
		MIX_PlayAudio(nullptr, sound);
	}
}

void MediaSound::setVolume(int volume) {
	(void)volume;
}

MIX_Audio *MediaSound::toSDL() {
	return sound;
}

