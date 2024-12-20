#include "MixerService.h"

#include <SDL_mixer.h>

#include <stdexcept>

MixerService::MixerService() : frequency(MIX_DEFAULT_FREQUENCY), channels(2) {
}

MixerService::MixerService(int frequency_, int channels_) : frequency(frequency_), channels(channels_) {
}

void MixerService::init() {
	if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, 2048) == -1) {
		throw std::runtime_error(Mix_GetError());
	}
}

void MixerService::destroy() {
	Mix_CloseAudio();
}

