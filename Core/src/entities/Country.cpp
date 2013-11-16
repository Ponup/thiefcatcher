#include "Country.h"

#include <Dimension.h>

Country::Country() {
}

Country::Country(const Country &country) {
	this->code = strdup( country.getCode() );
	this->id = country.getID();
	this->name = strdup(country.getName());
	this->description = strdup(country.getDescription());
	this->treasure = strdup(country.getTreasure());
	this->coord = country.getCoord();
	this->coin = strdup(country.getCoin());
	this->flagDesc = strdup(country.getFlagDescription());
	this->capital = strdup(country.getCapital());
	this->language = strdup(country.getLanguage());
}

Country & Country::operator=(const Country &country) {
	this->code = strdup( country.getCode() );
	this->id = country.getID();
	this->name = strdup(country.getName());
	this->description = strdup(country.getDescription());
	this->treasure = strdup(country.getTreasure());
	this->coord = country.getCoord();
	this->coin = strdup(country.getCoin());
	this->flagDesc = strdup(country.getFlagDescription());
	this->capital = strdup(country.getCapital());
	this->language = strdup(country.getLanguage());
	return *this;
}

void Country::setCode( const char *code ) {
	this->code = strdup( code );
}

const char* Country::getCode() const {
	return strdup( code );
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

void Country::setLanguage( const char *language ) {
	this->language = strdup( language );
}

const char* Country::getLanguage() const {
	return strdup( this->language );
}

void Country::setCapital( const char *capital ) {
	this->capital = strdup( capital );
}

const char* Country::getCapital() const {
	return strdup( capital );
}

void Country::setCoord(const Point & coord) {
	this->coord = coord;
}

Point Country::getCoord() const {
	return coord;
}

Surface *Country::getPhoto() const {
	char path[100];
	sprintf(path, "data/countries/%s/photo.jpg", code );
	
	return new Surface(path);
}

Surface *Country::getFlag() const {
	char path[100];
	sprintf(path, "data/countries/%s/miniflag.png", code );

	return new Surface(path);
}

const char *Country::toString() const {
	return strdup(name);
}
