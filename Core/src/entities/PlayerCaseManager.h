#pragma once

#include "entities/PlayerCase.h"
#include "entities/Player.h"

class PlayerCaseManager {

public:
	PlayerCaseManager();
	~PlayerCaseManager();
	
	static PlayerCase *createRandomCase( const Player &player );
	static void save( const PlayerCase &playerCase );
	static PlayerCase& load( int idPlayer );
};
