#include "Transitions.h"

#include <SDL.h>

Transitions::Transitions()
{
}

Transitions::~Transitions()
{
}

void Transitions::slideRL(Surface * window, Surface * newScreen) {
	SDL_Event e;
	for(int i = 800; i >= 0; i -= 20) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
				window->drawSurface(newScreen, Point(0, 0));
				window->flip();
				delete newScreen;
				return;
			}
		}
		Point newScreenPos(i, 0);
		Dimension newScreenDim(800 - i, 600);
		window->drawSurface(newScreen, newScreenPos);
		window->updateArea(newScreenPos, newScreenDim);
		SDL_Delay(10);
	}
	delete newScreen;
}

void Transitions::slideTB(Surface * window, Surface * newScreen) {
	const int diff = 25;
	
	for(int i = diff; i <= 600; i += diff) {
		Dimension newScreenDim(800, i);
		Surface * surf = newScreen->getArea(Point(0, 600 - i), newScreenDim);
		window->drawSurface(surf, Point(0, 0));
		delete surf;		
		window->updateArea(Point(0, 0), newScreenDim);
		SDL_Delay(5);
	}
	delete newScreen;
}

void Transitions::slideBT(Surface * window, Surface * newScreen) {
	const int diff = 25;
	
	for(int i = 600; i >= 0; i -= diff) {
		Point newScreenPos(0, i);
		Dimension newScreenDim(800, 600 - i);
		window->drawSurface(newScreen, newScreenPos);
		window->updateArea(newScreenPos, newScreenDim);
		SDL_Delay(5);
	}
	delete newScreen;
}
