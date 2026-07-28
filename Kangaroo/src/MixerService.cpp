#include "MixerService.h"

#include <SDL3_mixer/SDL_mixer.h>

#include <stdexcept>

MixerService::MixerService() : frequency(44100), channels(2) {
}

MixerService::MixerService(int frequency_, int channels_) : frequency(frequency_), channels(channels_) {
}

void MixerService::init() {
	if (!MIX_Init()) {
		throw std::runtime_error(SDL_GetError());
	}
}

void MixerService::destroy() {
	MIX_Quit();
}

