#ifndef HALLOFFAME_H
#define HALLOFFAME_H

#include <EventHandler.h>
#include <Surface.h>

#include <SDL.h>

class HallOfFameScreen : public EventHandler {
private:
	Surface * screen;
	bool quit;
	
public:
	HallOfFameScreen(Surface *screen);
	void show();
	
private:
	void onKeyDown(SDL_KeyboardEvent key);
	void onKeyUp(SDL_KeyboardEvent key);
	void onMouseButtonDown(SDL_MouseButtonEvent button);
	void onMouseButtonUp(SDL_MouseButtonEvent button);
	void onMouseMotion(SDL_MouseMotionEvent motion);	
};

#endif

