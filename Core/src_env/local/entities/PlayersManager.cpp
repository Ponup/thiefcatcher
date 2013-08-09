#include "entities/PlayersManager.h"

#include <string.h>

#include <Database.h>

#include "utilities/Translator.h"

vector<Player> PlayersManager::findTop10() {
	vector<Player> players;
	
	ResultSet & rs = Database::getInstance().execute("SELECT id, name, num_resolved_cases FROM player ORDER BY num_resolved_cases DESC LIMIT 10");
	for(unsigned int i = 0; i < rs.rowsCount(); i++) {
		Player player;
		player.setID(rs.getInt(i, 0));
		player.setName(rs.getString(i, 1));
		player.setResolved(rs.getInt(i, 2));
		players.push_back(player);
	}

	return players;
}

vector<int> PlayersManager::findAllPrimaryKeys() {
	vector<int> primaryKeys;

	ResultSet & rs = Database::getInstance().execute("SELECT id FROM player");
	for(unsigned int i = 0; i < rs.rowsCount(); i++) {
		primaryKeys.push_back(rs.getInt(i, 0));
	}

	return primaryKeys;	
}

Player *PlayersManager::findByPrimaryKey(int id) {
	Player *player = NULL;

	ResultSet &rs = Database::getInstance().execute("SELECT id, name, num_resolved_cases FROM player WHERE id = %d", id);
	if(rs.rowsCount() == 1) {
		player = new Player;
		player->setID(rs.getInt(0, 0));
		player->setName(rs.getString(0, 1));
		player->setResolved(rs.getInt(0, 2));						
	}

	return player;
}

Player *PlayersManager::findByName(const char *name) {
	Player *player = NULL;

	Database db = Database::getInstance();
	ResultSet &rs = db.execute("SELECT id, name, num_resolved_cases FROM player WHERE name = '%s'", name);
	if(rs.rowsCount() == 1) {
		player = new Player;
		player->setID(rs.getInt(0, 0));
		player->setName(rs.getString(0, 1));
		player->setResolved(rs.getInt(0, 2));
	}

	return player;
}

Player *PlayersManager::create(const char *name) {
	Database db = Database::getInstance();
	db.update("INSERT INTO player (id, name, num_resolved_cases) VALUES (NULL, '%s', 0)", name);

	return findByName(name);
}

void PlayersManager::updatePlayer(Player &player) {
	unsigned char numResolvedCases = player.getResolved() + 1;

	player.setResolved(numResolvedCases);
	
	Database db = Database::getInstance();
	db.update("UPDATE player SET num_resolved_cases = num_resolved_cases + 1 WHERE id = %d", player.getID());
}

const char *PlayersManager::getRank(const Player &player) {	
	Database db = Database::getInstance();
	ResultSet &rs = db.execute("SELECT description FROM player_rank WHERE %d >= resolved ORDER BY resolved DESC LIMIT 1", player.getResolved());
	if(rs.rowsCount() == 1) {
		return rs.getString(0, 0);
	} else {
		return _("Unknown");
	}
}

