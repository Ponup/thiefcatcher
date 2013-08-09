#include "PlayerCase.h"

#include <algorithm>
using std::random_shuffle;

#include <Random.h>

#include "entities/ClueManager.h"
#include "entities/CountriesManager.h"

#include "Vars.h"

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
	stolenObject = strdup(playerCase.getStolenObject());
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
	stolenObject = strdup(playerCase.getStolenObject());
	return *this;
}

PlayerCase::~PlayerCase() {
	delete startDate;
	delete currentDate;
	delete endDate;

	delete clues[2];
	delete clues[1];
	delete clues[0];

	delete clues;

	free(stolenObject);
}

void PlayerCase::setCriminal(Criminal &criminal) {
	this->criminal = criminal;
}

Criminal PlayerCase::getCriminal() const {
	return criminal;
}

void PlayerCase::setPlayer(Player & player) {
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

void PlayerCase::setStolenObject(const char *stolenObject) {
	this->stolenObject = strdup(stolenObject);
}

const char *PlayerCase::getStolenObject() const {
	return strdup(stolenObject);
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
	bool right = currentCountry.getID() == previousCountry().getID();
	printf("I am in the right country? %s\n", right ? "true" : "false");
	
	return right;
}

Country & PlayerCase::previousCountry() {
	Country & country = itinerary.at(currentPosition);
	printf("Previous country: %s\n", country.getName());
	return country;
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
	printf("\nUpdating countries\n");

	if(currentPosition + 1 == itinerary.size()) {
		printf("Pais final\n");
		return;
	}

	if (rightCountry()) {
		nextCountries[0] = nextCountry();
	} else {
		nextCountries[0] = previousCountry();
	}

	vector<int> countriesPK = Vars::listCountriesPK();
	int numCountries = countriesPK.size();

	int *keys = new int[numCountries - 1];
	memset(keys, '\0', numCountries - 1);
	for(int i = 0, x = 0; i < numCountries; i++) {
		if(countriesPK[i] != nextCountries[0].getID()) {
			keys[x] = countriesPK[i];
			x++;
		}
	}
	
	int *countriesPKazar = Random::nextArray(keys, numCountries - 1, 2);
	nextCountries[1] = *CountriesManager::findByPrimaryKey(countriesPKazar[0]);
	nextCountries[2] = *CountriesManager::findByPrimaryKey(countriesPKazar[1]);
	
	delete countriesPKazar;
	delete keys;	
	
	random_shuffle(nextCountries, nextCountries + 3);
}

void PlayerCase::updateClues() {
	if(currentPosition + 1 == itinerary.size()) {
		printf("Actualizando pistas en pais final\n");

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
		sprintf(text, "%sStolenObject: %s\n", text, itinerary[0].getTreasure());
	}
	for(unsigned int i = 0; i < itinerary.size(); i++) {
		sprintf(text, "%sFlight #%d: %s\n", text, i, itinerary[i].toString());
	}
	
	return text;
}

