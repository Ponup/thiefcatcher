#include "entities/PlayersManager.h"

#include <Database.h>
using Kangaroo::Database;

vector<Player> PlayersManager::findTop10() {
	vector<Player> players;

	const char *sql = "SELECT player.id, player.name, player.num_resolved_cases, player_rank.description FROM player INNER JOIN player_rank ON ( player_rank.resolved = player.num_resolved_cases ) ORDER BY num_resolved_cases DESC LIMIT 10";

	ResultSet &rs = Database::getInstance().execute(sql);
	while (rs.hasNext()) {
		Player player;
		player.setID(rs.getInt(0));
		player.setName(rs.getString(1));
		player.setResolved(rs.getInt(2));
		player.setRank(rs.getString(3));
		players.push_back(player);
	}

	return players;
}

vector<int> PlayersManager::findAllPrimaryKeys() {
	vector<int> primaryKeys;

	ResultSet & rs = Database::getInstance().execute("SELECT id FROM player");
	while (rs.hasNext()) {
		primaryKeys.push_back(rs.getInt(0));
	}

	return primaryKeys;
}

Player *PlayersManager::findByPrimaryKey(int id) {
	Player *player = nullptr;

	ResultSet &rs = Database::getInstance().execute("SELECT id, name, num_resolved_cases FROM player WHERE id = %d", id);
	if (rs.hasNext()) {
		player = new Player;
		player->setID(rs.getInt(0));
		player->setName(rs.getString(1));
		player->setResolved(rs.getInt(2));
	}

	return player;
}

Player *PlayersManager::findByName(const string &name) {
	Player *player = nullptr;

	Database &db = Database::getInstance();
	ResultSet &rs = db.execute("SELECT player.id, player.name, player.num_resolved_cases, player_rank.description FROM player INNER JOIN player_rank ON ( player_rank.resolved = player.num_resolved_cases ) WHERE player.name = '%s'", name.c_str());
	if (rs.hasNext()) {
		player = new Player;
		player->setID(rs.getInt(0));
		player->setName(rs.getString(1));
		player->setResolved(rs.getInt(2));
		player->setRank(rs.getString(3));
	}

	return player;
}

Player *PlayersManager::create(const string &name) {
	Database &db = Database::getInstance();
	db.update("INSERT INTO player (id, name, num_resolved_cases) VALUES (NULL, '%s', 0)", name.c_str());

	return findByName(name);
}

void PlayersManager::updatePlayer(Player &player) {
	unsigned char numResolvedCases = player.getResolved() + 1;

	player.setResolved(numResolvedCases);

	Database &db = Database::getInstance();
	db.update("UPDATE player SET num_resolved_cases = num_resolved_cases + 1 WHERE id = %d", player.getID());
}

