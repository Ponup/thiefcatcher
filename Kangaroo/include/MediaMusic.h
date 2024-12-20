#pragma once

#include <SDL_mixer.h>

class MediaMusic {
	
private:
	Mix_Music *music;

public:
	const static int ONE_TIME = 1;
	const static int FOREVER = -1;

	MediaMusic(const char *name);
	MediaMusic(const MediaMusic &mediaMusic);
	~MediaMusic();

	void play(int loops = -1);
	void stop();
	void fadeIn(int seconds = 5, int loops = -1);
	void fadeOut(int seconds = 5);
	bool isPlaying() const;
	bool isFading() const;

	Mix_Music *toSDL() const;
};

