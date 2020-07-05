#include "PlayerCaseManager.h"

#include <Database.h>
using Kangaroo::Database;

#include <Random.h>

#include "entities/PlayersManager.h"
#include "entities/CriminalsManager.h"
#include "entities/CountriesManager.h"

PlayerCaseManager::PlayerCaseManager()
{
    this->criminalIds = CriminalsManager::findAllPrimaryKeys();
}

PlayerCaseManager::~PlayerCaseManager()
{
}

PlayerCase *PlayerCaseManager::createRandomCase( const Player &player ) {
	PlayerCase *playerCase = new PlayerCase;
	playerCase->setPlayer(player);
	
	int *criminalsPKrandom = Random::nextArray(criminalIds, 1);
	Criminal *criminal = CriminalsManager::findByPrimaryKey(criminalsPKrandom[0]);
	delete criminalsPKrandom;
	playerCase->setCriminal(*criminal);
	
	vector<Country> itinerary = CountriesManager::findRandom(5);
	string stolenObject = itinerary[0].getPopularThings()[0];
	playerCase->setStolenObject( stolenObject );
	
	playerCase->itinerary = itinerary;
	playerCase->setCurrentCountry( itinerary[0] );

	playerCase->startDate = new DateTime;
	playerCase->currentDate = new DateTime;

	playerCase->endDate = new DateTime;
	playerCase->endDate->increase( 7, DateTime::Day );
	
	playerCase->updateCountries();
	playerCase->updateCountryPlaces();
	playerCase->updateClues();
	
	return playerCase;
}

void PlayerCaseManager::save( const PlayerCase &playerCase) {
	Database &db = Database::getInstance();

	db.execute( "DELETE FROM player_case WHERE id_player = %d", playerCase.player.getID() );
	db.execute( "DELETE FROM player_case_flight WHERE id_player = %d", playerCase.player.getID() );
	db.execute( "INSERT INTO player_case VALUES (%d, %d, 0)", playerCase.player.getID(), playerCase.criminal.getID() );
	
	for(unsigned int i = 0; i < playerCase.itinerary.size(); i++) {
		db.execute( "INSERT INTO player_case_flight VALUES (%d, %d, %d)", playerCase.player.getID(), i, playerCase.itinerary[i].getID() );
	}
}

PlayerCase &PlayerCaseManager::load( int idPlayer ) {
	PlayerCase *playerCase = new PlayerCase();
	
	Database &db = Database::getInstance();
	
	ResultSet &rs = db.execute( "SELECT id_player, id_criminal, current_position FROM player_case WHERE id_player = %d", idPlayer);
	if(rs.hasNext()) {
		int id_player = rs.getInt(0);
		int id_criminal = rs.getInt(1);
		int current_position = rs.getInt(2);
		Player *player = PlayersManager::findByPrimaryKey(id_player);
		playerCase->setPlayer(*player);
		playerCase->setCriminal(*CriminalsManager::findByPrimaryKey(id_criminal));
		playerCase->setCurrentPosition(current_position);
	}
	
	ResultSet &rs1 = db.execute( "SELECT id_country FROM player_case_flight WHERE id_player = %d ORDER BY position ASC", idPlayer);
	vector<Country> countries;
	while (rs1.hasNext()) {
		int id_country = rs1.getInt(0);
		Country country = CountriesManager::findByPrimaryKey(id_country);
		countries.push_back(country);
	}
	playerCase->itinerary = countries;
		
	return *playerCase;
}


