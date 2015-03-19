#include "PlayerCase.h"

#include <algorithm>
using std::random_shuffle;

#include <Random.h>

#include "entities/ClueManager.h"
#include "entities/CountriesManager.h"

#include "utilities/Translator.h"

PlayerCase::PlayerCase() {
	currentPosition = 0;
	captureOrderExecuted = false;
}

PlayerCase::PlayerCase(const PlayerCase &playerCase) {
	startDate = playerCase.startDate;
	currentDate = playerCase.currentDate;
	endDate = playerCase.endDate;
	player = playerCase.getPlayer();
	criminal = playerCase.getCriminal();
	currentPosition = playerCase.getCurrentPosition();
	itinerary = playerCase.getItinerary();
	captureOrderExecuted = playerCase.isCaptureOrderExecuted();
	stolenObject = playerCase.getStolenObject();
}

PlayerCase PlayerCase::operator=(const PlayerCase &playerCase) {
	startDate = playerCase.startDate;
	currentDate = playerCase.currentDate;
	endDate = playerCase.endDate;
	player = playerCase.getPlayer();
	criminal = playerCase.getCriminal();	
	currentPosition = playerCase.getCurrentPosition();
	itinerary = playerCase.getItinerary();
	captureOrderExecuted = playerCase.isCaptureOrderExecuted();
	stolenObject = playerCase.getStolenObject();
	return *this;
}

PlayerCase::~PlayerCase() {
	delete startDate;
	delete currentDate;
	delete endDate;

	delete clues[2];
	delete clues[1];
	delete clues[0];
}

void PlayerCase::setCriminal( const Criminal &criminal ) {
	this->criminal = criminal;
}

Criminal PlayerCase::getCriminal() const {
	return criminal;
}

void PlayerCase::setPlayer( const Player &player ) {
	this->player = player;
}

Player PlayerCase::getPlayer() const {
	return player;
}

void PlayerCase::setCurrentPosition(int currentPosition) {
	this->currentPosition = currentPosition;
}

int PlayerCase::getCurrentPosition() const {
	return currentPosition;
}

void PlayerCase::setStolenObject( const string &stolenObject ) {
	this->stolenObject = stolenObject;
}

string PlayerCase::getStolenObject() const {
	return stolenObject;
}

bool PlayerCase::isCaptureOrderExecuted() const {
	return captureOrderExecuted;
}

void PlayerCase::setCaptureOrderExecuted(bool captureOrderExecuted) {
	this->captureOrderExecuted = captureOrderExecuted;
}

void PlayerCase::setItinerary(vector<Country> itinerary) {
	this->itinerary = itinerary;
}

vector<Country> PlayerCase::getItinerary() const {
	return itinerary;
}

bool PlayerCase::rightCountry() {
	return ( currentCountry.getID() == previousCountry().getID() );
}

Country & PlayerCase::previousCountry() {
	return itinerary.at(currentPosition);
}

Country & PlayerCase::getCurrentCountry() {
	return currentCountry;
}

Country & PlayerCase::nextCountry() {
	return itinerary.at(currentPosition + 1);
}

Country & PlayerCase::getLastCountry() {
	return itinerary[currentPosition];
}

void PlayerCase::setCurrentCountry(const Country & country) {
	this->currentCountry = country;
}

void PlayerCase::updateCountries() {
	if(currentPosition + 1 == itinerary.size()) {
		return;
	}

	nextCountries[0] = ( rightCountry() ? nextCountry() : previousCountry() );

	vector<Country> randomCountries = CountriesManager::findRandom( 3 );
	for( int i = 0, pos = 1; i < 3 && pos < 3; i++ ) {
		if( randomCountries[ i ].getID() == nextCountries[0].getID() ) {
			continue;
		}

		nextCountries[ pos ] = randomCountries[ i ];
		pos++;
	}

	random_shuffle( nextCountries, nextCountries + 3 );
}

void PlayerCase::updateClues() {
	if(currentPosition + 1 == itinerary.size()) {
		Clue clue(_("You are close to catch him!"));

		clues[0] = clues[1] = clues[2] = &clue;
	} else {
		Criminal criminal = getCriminal();
		Country next = nextCountry();

		clues[0] = ClueManager::create(criminal, next);
		clues[1] = ClueManager::create(criminal, next);
		clues[2] = ClueManager::create(criminal, next);
	}
}

const char *PlayerCase::toString() const {
	char *text = (char *)calloc(800, sizeof(char));
	if(!text) return NULL;

	sprintf(text, "Player: %s\n", player.toString());
	sprintf(text, "%sCriminal: %s\n", text, criminal.toString());
	sprintf(text, "%sStart date: %s\n", text, startDate->toString("%A %d, %H:%M"));
	sprintf(text, "%sEnd date: %s\n", text, endDate->toString("%A %d, %H:%M"));
	if(itinerary.size() > 0) {
		sprintf(text, "%sStolenObject: %s\n", text, itinerary[0].getTreasure().c_str());
	}
	for(unsigned int i = 0; i < itinerary.size(); i++) {
		sprintf(text, "%sFlight #%d: %s\n", text, i, itinerary[i].toString().c_str());
	}
	
	return text;
}

