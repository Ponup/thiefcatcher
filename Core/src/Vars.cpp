#include "Vars.h"

#include "entities/CriminalsManager.h"

vector<int> Vars::criminalsPK;

void Vars::init() {
	criminalsPK = CriminalsManager::findAllPrimaryKeys();
}

vector<int> &Vars::listCriminalsPK() {
	return criminalsPK;
}

