#pragma once

#include <SDL.h>

/**
 * Color definition, taking four parameters (r, g, b and a channel)
 */
class Color : public SDL_Color {

public:
	Color();
	Color( Uint8 r, Uint8 g, Uint8 b );
	Color( Uint8 r, Uint8 g, Uint8 b, Uint8 a );
	
	Uint32 toSDL( SDL_Surface* surface ) const;
};

