#ifndef PLAYERSMANAGER_H
#define PLAYERSMANAGER_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "entities/Player.h"

class PlayersManager {
	
public:
	static vector<Player> findTop10();
	static vector<int> findAllPrimaryKeys();

	static Player* findByPrimaryKey(int id);
	static Player* findByName( string name );
		
	static Player* create( string name );
		
	static void updatePlayer(Player &player);
};

#endif

