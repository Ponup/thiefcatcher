#include "FontService.h"

#include <SDL3_ttf/SDL_ttf.h>

void FontService::init() {
	initialized = TTF_Init();
	if (!initialized)
	{
		throw runtime_error(SDL_GetError());
	}
}

void FontService::destroy() {
	if (initialized) {
		TTF_Quit();
	}
}

