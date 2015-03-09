#include "Vars.h"

#include "entities/CriminalsManager.h"
#include "entities/CountriesManager.h"

vector<int> Vars::criminalsPK;
vector<int> Vars::countriesPK;

void Vars::init() {
	criminalsPK = CriminalsManager::findAllPrimaryKeys();
	countriesPK = CountriesManager::findAllPrimaryKeys();
}

vector<int> &Vars::listCriminalsPK() {
	return criminalsPK;
}

vector<int> &Vars::listCountriesPK() {
	return countriesPK;
}
