#pragma once

#include <SDL3/SDL.h>

#include <stdexcept>
using std::runtime_error;

#include "Service.h"


/**
 * This service initializes the SDL library.
 * 
 * @see Service 
 */
class CoreService : public Service {
	
private:
	Uint32 flags;

public:
	CoreService( Uint32 flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO );
	void init();
	void destroy();
};

