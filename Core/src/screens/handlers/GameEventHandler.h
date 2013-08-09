#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include <EventHandler.h>

#include "screens/Game.h"

class GameEventHandler : public EventHandler {
	private:
		Game *game;
		SensitiveAreas sensAreas;		
		
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

#endif

