#include "MediaMusic.h"

#include <stdexcept>
using std::runtime_error;

MediaMusic::MediaMusic(const char *name) {
	music = Mix_LoadMUS(name);
	if (!music) {
		throw runtime_error( Mix_GetError() );
	}
}

MediaMusic::MediaMusic(const MediaMusic & mediaMusic) {
	music = mediaMusic.toSDL();
}

MediaMusic::~MediaMusic() {
	Mix_FreeMusic(music);
}

void MediaMusic::play(int loops) {
	if (music != nullptr) {
		if (Mix_PlayMusic(music, loops) == -1) {
			throw runtime_error( Mix_GetError() );
		}
	}
}

void MediaMusic::stop() {
	if (Mix_PlayingMusic()) {
		Mix_HaltMusic();
	}
}

void MediaMusic::fadeIn(int seconds, int loops) {
	if (Mix_FadeInMusic(music, loops, seconds*1000) == -1) {
		throw runtime_error( Mix_GetError() );
	}
}

void MediaMusic::fadeOut(int seconds) {
	if (Mix_FadeOutMusic(seconds*1000) == 0) {
		throw runtime_error( Mix_GetError() );
	}
}

bool MediaMusic::isPlaying() const {
	return Mix_PlayingMusic();
}

bool MediaMusic::isFading() const {
	switch (Mix_FadingMusic()) {
	case MIX_FADING_OUT:
	case MIX_FADING_IN:
		return true;
	case MIX_NO_FADING:
	default:
		return false;
	}
}

Mix_Music *MediaMusic::toSDL() const {
	return music;
}
