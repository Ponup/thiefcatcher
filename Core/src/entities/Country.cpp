#include "Country.h"

#include <Dimension.h>

#include <string>
using std::string;

Country::Country() {
}

Country::Country(const Country &country) {
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

Country& Country::operator=(const Country &country) {
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

void Country::setIsoCode(const string &isoCode) {
    this->isoCode = isoCode;
}

string Country::getIsoCode() const {
    return isoCode;
}

void Country::setCode(const string &code) {
    this->code = code;
}

string Country::getCode() const {
    return code;
}

Country::~Country() {
}

void Country::setID(CountryId id) {
    this->id = id;
}

CountryId Country::getID() const {
    return id;
}

void Country::setName(const string &name) {
    this->name = name;
}

string Country::getName() const {
    return name;
}

void Country::setDescription(const string &description) {
    this->description = description;
}

string Country::getDescription() const {
    return description;
}

void Country::setFlagDescription(const string &flagDesc) {
    this->flagDesc = flagDesc;
}

string Country::getFlagDescription() const {
    return flagDesc;
}

void Country::setTreasure(const string &treasure) {
    this->treasure = treasure;
}

string Country::getTreasure() const {
    return treasure;
}

void Country::setLanguages(const vector<string> &languages) {
    this->languages = languages;
}

const vector<string> Country::getLanguages() const {
    return languages;
}

void Country::setCurrencies(const vector<string> &currencies) {
    this->currencies = currencies;
}

const vector<string> Country::getCurrencies() const {
    return currencies;
}

string Country::getFirstCurrency(void) const {
    return currencies.size() > 0 ? currencies.at(0) : "unknown";
}

void Country::setCapital(const string &capital) {
    this->capital = capital;
}

string Country::getCapital() const {
    return capital;
}

void Country::setLatitude(double latitude) {
    this->latitude = latitude;
}

double Country::getLatitude() const {
    return latitude;
}

void Country::setLongitude(double longitude) {
    this->longitude = longitude;
}

double Country::getLongitude() const {
    return longitude;
}

pair<double, double> Country::getLatitudeLongitude() const {
    return pair<double, double>(latitude, longitude);
}

bool operator==(const Country& leftHandCountry, const Country& rightHandCountry) {
    return leftHandCountry.getID() == rightHandCountry.getID();
}
