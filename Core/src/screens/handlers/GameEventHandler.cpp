#include "GameEventHandler.h"

GameEventHandler::GameEventHandler(Game * game_) : game(game_) {
	sensAreas.addArea(Area(416, 402, 62, 62));	
	sensAreas.addArea(Area(554, 402, 62, 62));
	sensAreas.addArea(Area(623, 402, 62, 62));
	sensAreas.addArea(Area(691, 402, 62, 62));
}

void GameEventHandler::onMouseMotion(SDL_MouseMotionEvent motion) {
	int resolved = sensAreas.resolve(motion.x, motion.y);
	if(resolved != -1) {
		game->currentOption = resolved;
	}
}

void GameEventHandler::onMouseButtonDown(SDL_MouseButtonEvent button) {
	int resolved = sensAreas.resolve(button.x, button.y);
	if(resolved != -1) {
		game->currentOption = resolved;
		if(button.button == SDL_BUTTON_LEFT) {
			game->enterOption();
		}
	}	
}

void GameEventHandler::onMouseButtonUp(SDL_MouseButtonEvent button) {
}

void GameEventHandler::onKeyDown(SDL_KeyboardEvent key) {
	switch(key.keysym.sym) {
		case SDLK_ESCAPE:
			game->quitGame();
			break;
		case SDLK_q:
			if(key.keysym.mod & KMOD_CTRL) {
				game->quitGame();
			}
			break;
		case SDLK_F4:
			game->getWindow()->toggleFullScreen();
			break;
		case SDLK_LEFT:
			game->currentOption--;
			if(game->currentOption == -1) game->currentOption = 3;
			game->updateOption();					
			break;
		case SDLK_RIGHT:
			game->currentOption++;
			if(game->currentOption > 3) game->currentOption = 0;
			game->updateOption();
			break;
		case SDLK_RETURN:
			game->enterOption();
			break;
		default:
			break;
	}	
}

void GameEventHandler::onKeyUp(SDL_KeyboardEvent key) {
}

void GameEventHandler::onQuit(SDL_QuitEvent quit) {
	game->quitGame();	
}
