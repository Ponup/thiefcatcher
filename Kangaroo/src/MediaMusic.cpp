#include "MediaMusic.h"

#include <stdexcept>
using std::runtime_error;

MediaMusic::MediaMusic(const char *name) {
	music = MIX_LoadAudio(nullptr, name, true);
	if (!music) {
		throw runtime_error( SDL_GetError() );
	}
}

MediaMusic::MediaMusic(const MediaMusic & mediaMusic) {
	music = mediaMusic.toSDL();
}

MediaMusic::~MediaMusic() {
	if (music) {
		MIX_DestroyAudio(music);
	}
}

void MediaMusic::play(int loops) {
	(void)loops;
	if (music != nullptr) {
		MIX_PlayAudio(nullptr, music);
	}
}

void MediaMusic::stop() {
}

void MediaMusic::fadeIn(int seconds, int loops) {
	(void)seconds;
	play(loops);
}

void MediaMusic::fadeOut(int seconds) {
	(void)seconds;
}

bool MediaMusic::isPlaying() const {
	return false;
}

bool MediaMusic::isFading() const {
	return false;
}

MIX_Audio *MediaMusic::toSDL() const {
	return music;
}
