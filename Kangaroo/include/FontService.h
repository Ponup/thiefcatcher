#pragma once

#include "Service.h"

#include <stdexcept>
using std::runtime_error;

/**
 * This service initializes the SDL_ttf library.
 *
 * @see Service
 */
class FontService : public Service {

	bool initialized;

public:
	void init();
	void destroy();
};

