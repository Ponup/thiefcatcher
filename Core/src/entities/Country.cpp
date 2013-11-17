#include "Country.h"

#include <Dimension.h>

#include <boost/filesystem.hpp>

Country::Country() {
}

Country::Country(const Country &country) {
	this->id = country.getID();
	this->isoCode = strdup( country.getIsoCode() );
	this->code = strdup( country.getCode() );
	this->name = strdup(country.getName());
	this->description = strdup(country.getDescription());
	this->treasure = strdup(country.getTreasure());
	this->coord = country.getCoord();
	this->flagDesc = strdup(country.getFlagDescription());
	this->capital = strdup(country.getCapital());
	this->languages = country.getLanguages();
	this->currencies = country.getCurrencies();
}

Country& Country::operator=(const Country &country) {
	this->id = country.getID();
	this->code = strdup( country.getCode() );
	this->isoCode = strdup( country.getIsoCode() );
	this->name = strdup(country.getName());
	this->description = strdup(country.getDescription());
	this->treasure = strdup(country.getTreasure());
	this->coord = country.getCoord();
	this->flagDesc = strdup(country.getFlagDescription());
	this->capital = strdup(country.getCapital());
	this->languages = country.getLanguages();
	this->currencies = country.getCurrencies();
	return *this;
}

void Country::setIsoCode( const char *isoCode ) {
	this->isoCode = strdup( isoCode );
}

const char* Country::getIsoCode() const {
	return strdup( isoCode );
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

void Country::setLanguages( const vector<string> &languages ) {
	this->languages = languages;
}

const vector<string> Country::getLanguages() const {
	return languages;
}

void Country::setCurrencies( const vector<string> &currencies ) {
	this->currencies = currencies;
}

const vector<string> Country::getCurrencies() const {
	return currencies;
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
	sprintf(path, "data/countries/%s/postal.png", isoCode );

	return boost::filesystem::exists( path ) ? new Surface( path ) : NULL;
}

Surface *Country::getFlag() const {
	char path[100];
	sprintf(path, "data/countries/%s/flag.png", isoCode );

	return new Surface(path);
}

const char *Country::toString() const {
	return strdup(name);
}
