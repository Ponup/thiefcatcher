#pragma once

#include "entities/PlayerCase.h"
#include "entities/Player.h"

class PlayerCaseManager {

public:
	PlayerCaseManager();
	~PlayerCaseManager();
	
	static PlayerCase *createRandomCase(Player &player);
	static void save(PlayerCase *playerCase);
	static PlayerCase &load(int idPlayer);
};
