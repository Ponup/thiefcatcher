#pragma once

#include <EventHandler.h>

#include "screens/Game.h"

#include <MouseCursor.h>
using Kangaroo::MouseCursor;

class GameEventHandler : public EventHandler {

	Game *game;
	SensitiveAreas sensAreas;
	MouseCursor normalCursor, handCursor;

public:
	GameEventHandler(Game *game);
	virtual ~GameEventHandler() {}

private:
	void onMouseMotion(SDL_MouseMotionEvent);
	void onMouseButtonDown(SDL_MouseButtonEvent);
	void onMouseButtonUp(SDL_MouseButtonEvent);
	void onKeyDown(SDL_KeyboardEvent);
	void onKeyUp(SDL_KeyboardEvent);
	void onQuit(SDL_QuitEvent);
};
