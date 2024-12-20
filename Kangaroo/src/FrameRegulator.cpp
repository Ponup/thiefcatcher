#include "FrameRegulator.h"

#include <SDL.h>

void FrameRegulator::setUp() {
	referenceTime = SDL_GetTicks();
}

void FrameRegulator::regulate() {
	if(SDL_GetTicks() < referenceTime + framePause)
		SDL_Delay(10);

	referenceTime = SDL_GetTicks();
}

