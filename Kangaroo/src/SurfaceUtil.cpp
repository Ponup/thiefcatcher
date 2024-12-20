#include "SurfaceUtil.h"

Point SurfaceUtil::drawCentered(Surface *surface, Surface *parent) {
	SDL_Surface *surfaceSDL = surface->toSDL();
	SDL_Surface *parentSDL = parent->toSDL();
	SDL_Rect rect;
	rect.x = (parentSDL->w >> 1) - (surfaceSDL->w >> 1);
	rect.y = (parentSDL->h >> 1) - (surfaceSDL->h >> 1);

	SDL_BlitSurface(surfaceSDL, 0, parentSDL, &rect);
	
	return Point(rect.x, rect.y);
}

Point SurfaceUtil::getCentered(Surface * surface, Surface * parent) {
	SDL_Surface *surfaceSDL = surface->toSDL();
	SDL_Surface *parentSDL = parent->toSDL();

	return Point((parentSDL->w >> 1) - (surfaceSDL->w >> 1), (parentSDL->h >> 1) - (surfaceSDL->h >> 1));
}

bool SurfaceUtil::fadeIn(Surface * surface, Surface * parent, const Point & to) {
	SDL_Surface *image = surface->toSDL();
	SDL_Surface *screen = parent->toSDL();

	SDL_Surface *backup = parent->getArea(to, surface->getDimension())->toSDL();

	SDL_Rect destination;
	destination.x = to.x;
	destination.y = to.y;
	destination.w = image->w;
	destination.h = image->h;
			
	SDL_Event e;
	bool quit = false;
	
	for(int alpha = SDL_ALPHA_TRANSPARENT; alpha < SDL_ALPHA_OPAQUE && quit == false; alpha++) {
		// Draw the background surface
		SDL_BlitSurface(backup, nullptr, screen, &destination);
		// Set the transparency
		//SDL_SetAlpha(image, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
		// Draw the alpha image
		SDL_BlitSurface(image, nullptr, screen, &destination);
		// Update the surface
		//SDL_UpdateRect(screen, destination.x, destination.y, destination.w, destination.h);
		
		SDL_Delay(10);
		
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
			}
		}
	}
	
	return quit;
}

bool SurfaceUtil::fadeOut(Surface * surface, Surface * parent, const Point & to) {
	SDL_Surface * image = surface->toSDL();
	SDL_Surface * screen = parent->toSDL();

	SDL_Surface * backup = parent->getArea(to, surface->getDimension())->toSDL();

	SDL_Rect destination;
	destination.x = to.x;
	destination.y = to.y;
	destination.w = image->w;
	destination.h = image->h;
	
	SDL_Event e;
	bool quit = false;	
			
	for(int alpha = SDL_ALPHA_OPAQUE; alpha > SDL_ALPHA_TRANSPARENT && quit == false; alpha--) {
		// Draw the background surface
		SDL_BlitSurface(backup, nullptr, screen, &destination);
		// Set the transparency
		//SDL_SetAlpha(image, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
		// Draw the alpha image
		SDL_BlitSurface(image, nullptr, screen, &destination);
		// Update the surface
		//SDL_UpdateRect(screen, destination.x, destination.y, destination.w, destination.h);
		
		SDL_Delay(10);
		
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
			}
		}
	}
	
	return quit;	
}
