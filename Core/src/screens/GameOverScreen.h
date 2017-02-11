#pragma once

#include <Renderer.h>
using Kangaroo::Renderer;

#include "Game.h"
#include "utilities/Translator.h"
#include "entities/PlayerCase.h"
#include "screens/ComputerScreen.h"

class GameOverScreen : public ComputerScreen {

	Game* game;
	PlayerCase* playerCase;

public:
	GameOverScreen(Renderer* renderer, Game* game, PlayerCase* playerCase);
	void show();
};