#include "PlayerCaseManager.h"

#include <Database.h>
using Kangaroo::Database;

#include <Random.h>

#include "Vars.h"

#include "entities/PlayersManager.h"
#include "entities/CriminalsManager.h"
#include "entities/CountriesManager.h"

PlayerCaseManager::PlayerCaseManager()
{
}

PlayerCaseManager::~PlayerCaseManager()
{
}

PlayerCase *PlayerCaseManager::createRandomCase(Player &player) {
	PlayerCase *playerCase = new PlayerCase;
	playerCase->setPlayer(player);
	
	int *criminalsPKrandom = Random::nextArray(Vars::listCriminalsPK(), 1);
	Criminal *criminal = CriminalsManager::findByPrimaryKey(criminalsPKrandom[0]);
	delete criminalsPKrandom;
	playerCase->setCriminal(*criminal);
	
	int *countriesPKrandom = Random::nextArray(Vars::listCountriesPK(), 7);

	vector<Country> itinerary;
	for(unsigned int i = 0; i < 7; i++) {
		Country country = CountriesManager::findByPrimaryKey( countriesPKrandom[i] );
		itinerary.push_back(country);
	}
	const char *sto = itinerary[0].getTreasure().c_str();
	playerCase->setStolenObject(sto);
	
	playerCase->itinerary = itinerary;
	playerCase->setCurrentCountry(CountriesManager::findByPrimaryKey(countriesPKrandom[0]));
	delete countriesPKrandom;

	playerCase->startDate = new DateTime;
	playerCase->currentDate = new DateTime;

	playerCase->endDate = new DateTime;
	playerCase->endDate->increase(7, DateTime::Day);
	//playerCase->endDate->increase(7, DateTime::Hour);
	
	playerCase->updateCountries();
	playerCase->updateClues();
	
	printf("%s\n", playerCase->toString());
	
	return playerCase;
}

void PlayerCaseManager::save(PlayerCase *playerCase) {
	const char sql0[] = "DELETE FROM player_case WHERE id_player = %d";
	Database::getInstance().execute(sql0, playerCase->player.getID());

	const char sql1[] = "DELETE FROM player_case_flight WHERE id_player = %d";
	Database::getInstance().execute(sql1, playerCase->player.getID());
	
	const char sql2[] = "INSERT INTO player_case VALUES (%d, %d, 0)";
	Database::getInstance().execute(sql2, playerCase->player.getID(), playerCase->criminal.getID());
	
	for(unsigned int i = 0; i < playerCase->itinerary.size(); i++) {
		const char sql3[] = "INSERT INTO player_case_flight VALUES (%d, %d, %d)";
		Database::getInstance().execute(sql3, playerCase->player.getID(), i, playerCase->itinerary[i].getID());
	}
}

PlayerCase &PlayerCaseManager::load(int idPlayer) {
	PlayerCase *playerCase = new PlayerCase();
	
	const char sql0[] = "SELECT id_player, id_criminal, current_position FROM player_case WHERE id_player = %d";
	ResultSet & rs = Database::getInstance().execute(sql0, idPlayer);
	if(rs.hasNext()) {
		int id_player = rs.getInt(0);
		int id_criminal = rs.getInt(1);
		int current_position = rs.getInt(2);
		Player *player = PlayersManager::findByPrimaryKey(id_player);
		playerCase->setPlayer(*player);
		playerCase->setCriminal(*CriminalsManager::findByPrimaryKey(id_criminal));
		playerCase->setCurrentPosition(current_position);
	}
	
	const char sql1[] = "SELECT id_country FROM player_case_flight WHERE id_player = %d ORDER BY position ASC";
	ResultSet & rs1 = Database::getInstance().execute(sql1, idPlayer);
	vector<Country> countries;
	while (rs1.hasNext()) {
		int id_country = rs1.getInt(0);
		Country country = CountriesManager::findByPrimaryKey(id_country);
		countries.push_back(country);
	}
	playerCase->itinerary = countries;
		
	return *playerCase;
}


