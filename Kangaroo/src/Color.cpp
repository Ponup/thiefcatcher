#include "Color.h"

Color::Color() {
	r = g = b = 0;
	a = SDL_ALPHA_OPAQUE;
}

Color::Color( Uint8 r_, Uint8 g_, Uint8 b_ ) {
	r = r_;
	g = g_;
	b = b_;
	a = SDL_ALPHA_OPAQUE;
}

Color::Color( Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_ ) {
	r = r_;
	g = g_;
	b = b_;
	a = a_;
}

Uint32 Color::toSDL( SDL_Surface* surface ) const {
	return SDL_MapRGB( surface->format, r, g, b );
}

