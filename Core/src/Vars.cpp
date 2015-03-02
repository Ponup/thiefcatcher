#include "Vars.h"

#include "entities/CriminalsManager.h"
#include "entities/CountriesManager.h"
#include "entities/PlacesManager.h"

vector<int> Vars::criminalsPK;
vector<int> Vars::countriesPK;
vector<int> Vars::placesPK;

void Vars::init() {
	criminalsPK = CriminalsManager::findAllPrimaryKeys();
	countriesPK = CountriesManager::findAllPrimaryKeys();
	placesPK = PlacesManager::findAllPrimaryKeys();		
}

vector<int> &Vars::listCriminalsPK() {
	return criminalsPK;
}

vector<int> &Vars::listCountriesPK() {
	return countriesPK;
}

vector<int> &Vars::listPlacesPK() {
	return placesPK;
}

