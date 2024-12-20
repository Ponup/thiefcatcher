#include "FontService.h"

#include <SDL_ttf.h>

void FontService::init() {
	initialized = TTF_Init() == 0;
	if (!initialized)
	{
		throw runtime_error(TTF_GetError());
	}
}

void FontService::destroy() {
	if (initialized) {
		TTF_Quit();
	}
}

