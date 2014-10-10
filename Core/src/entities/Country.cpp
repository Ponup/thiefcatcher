#include "Country.h"

#include <Dimension.h>

#include <fstream>

Country::Country() {
}

Country::Country( const Country &country ) {
	this->id = country.getID();
	this->isoCode = country.getIsoCode();
	this->code = country.getCode();
	this->name = country.getName();
	this->description = country.getDescription();
	this->treasure = country.getTreasure();
	this->flagDesc = country.getFlagDescription();
	this->capital = country.getCapital();
	this->languages = country.getLanguages();
	this->currencies = country.getCurrencies();
	this->latitude = country.getLatitude();
	this->longitude = country.getLongitude();
}

Country& Country::operator=( const Country &country ) {
	this->id = country.getID();
	this->code = country.getCode();
	this->isoCode = country.getIsoCode();
	this->name = country.getName();
	this->description = country.getDescription();
	this->treasure = country.getTreasure();
	this->flagDesc = country.getFlagDescription();
	this->capital = country.getCapital();
	this->languages = country.getLanguages();
	this->currencies = country.getCurrencies();
	this->latitude = country.getLatitude();
	this->longitude = country.getLongitude();
	return *this;
}

void Country::setIsoCode( string isoCode ) {
	this->isoCode = isoCode;
}

string Country::getIsoCode() const {
	return isoCode;
}

void Country::setCode( string code ) {
	this->code = code;
}

string Country::getCode() const {
	return code;
}

Country::~Country() {
}

void Country::setID(unsigned char id) {
	this->id = id;
}

unsigned char Country::getID() const {
	return id;
}

void Country::setName(string name) {
	this->name = name;
}

string Country::getName() const {
	return name;
}

void Country::setDescription(string description) {
	this->description = description;
}

string Country::getDescription() const {
	return description;
}

void Country::setFlagDescription(string flagDesc) {
	this->flagDesc = flagDesc;
}

string Country::getFlagDescription() const {
	return flagDesc;
}

void Country::setTreasure(string treasure) {
	this->treasure = treasure;
}

string Country::getTreasure() const {
	return treasure;
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

void Country::setCapital( string capital ) {
	this->capital = capital;
}

string Country::getCapital() const {
	return capital;
}

void Country::setLatitude( double latitude )
{
	this->latitude = latitude;
}

double Country::getLatitude() const
{
	return latitude;
}

void Country::setLongitude( double longitude )
{
	this->longitude = longitude;
}

double Country::getLongitude() const
{
	return longitude;
}
		
pair<double, double> Country::getLatitudeLongitude() const
{
	return pair<double, double>( latitude, longitude );
}

bool fileExists( const std::string& name )
{
	std::ifstream f( name.c_str() );
	return f.is_open();
}

Surface* Country::getPhoto() const {
	char path[100];
	sprintf(path, "data/countries/%s/postal.png", isoCode.c_str() );

	return new Surface( fileExists( path ) ? path : "resources/images/notebook.png" );
}

Surface *Country::getFlag() const {
	char path[100];
	sprintf(path, "data/countries/%s/flag.png", isoCode.c_str() );

	return new Surface(path);
}

string Country::toString() const {
	return name;
}

