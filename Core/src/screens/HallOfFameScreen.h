#pragma once

#include <EventHandler.h>
#include <Window.h>

#include <SDL.h>

#include <Renderer.h>

using Kangaroo::Renderer;

class HallOfFameScreen : public EventHandler {

	Renderer* renderer;
	bool quit;

public:
	HallOfFameScreen(Renderer* renderer);
	void show();

private:
	void onKeyDown(SDL_KeyboardEvent key);
	void onKeyUp(SDL_KeyboardEvent key);
	void onMouseButtonDown(SDL_MouseButtonEvent button);
	void onMouseButtonUp(SDL_MouseButtonEvent button);
	void onMouseMotion(SDL_MouseMotionEvent motion);
};

