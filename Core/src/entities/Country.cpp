#include "Country.h"

#include <Dimension.h>

Country::Country() {
}

Country::Country(const Country &country) {
	this->id = country.getID();
	this->name = strdup(country.getName());
	this->description = strdup(country.getDescription());
	this->treasure = strdup(country.getTreasure());
	this->coord = country.getCoord();
	this->coin = strdup(country.getCoin());
	this->flagDesc = strdup(country.getFlagDescription());
}

Country & Country::operator=(const Country &country) {
	this->id = country.getID();
	this->name = strdup(country.getName());
	this->description = strdup(country.getDescription());
	this->treasure = strdup(country.getTreasure());
	this->coord = country.getCoord();
	this->coin = strdup(country.getCoin());
	this->flagDesc = strdup(country.getFlagDescription());
	return *this;
}

Country::~Country() {
}

void Country::setID(unsigned char id) {
	this->id = id;
}

unsigned char Country::getID() const {
	return id;
}

void Country::setName(const char *name) {
	this->name = strdup(name);
}

const char *Country::getName() const {
	return strdup(name);
}

void Country::setDescription(const char *description) {
	this->description = strdup(description);
}

const char *Country::getDescription() const {
	return strdup(description);
}

void Country::setCoin(const char *coin) {
	this->coin = strdup(coin);
}

const char *Country::getCoin() const {
	return strdup(coin);
}

void Country::setFlagDescription(const char *flagDesc) {
	this->flagDesc = strdup(flagDesc);
}

const char *Country::getFlagDescription() const {
	return strdup(flagDesc);
}

void Country::setTreasure(const char *treasure) {
	this->treasure = strdup(treasure);
}

const char *Country::getTreasure() const {
	return strdup(treasure);
}

void Country::setCoord(const Point & coord) {
	this->coord = coord;
}

Point Country::getCoord() const {
	return coord;
}

Surface *Country::getPhoto() const {
	char path[100];
	sprintf(path, "data/countries/%d/photo.jpg", getID());
	
	return new Surface(path);
}

Surface *Country::getFlag() const {
	char path[100];
	sprintf(path, "data/countries/%d/miniflag.png", getID());

	return new Surface(path);
}

const char *Country::toString() const {
	return strdup(name);
}
