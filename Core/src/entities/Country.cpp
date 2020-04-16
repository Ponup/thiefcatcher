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
    this->flag = country.getFlag();
    this->continent = country.getContinent();
    this->capital = country.getCapital();
    this->popularThings = country.getPopularThings();
    this->languages = country.getLanguages();
    this->currencies = country.getCurrencies();
    this->coordinates = country.getCoordinates();
}

Country& Country::operator=(const Country &country) {
    this->id = country.getID();
    this->code = country.getCode();
    this->isoCode = country.getIsoCode();
    this->name = country.getName();
    this->flag = country.getFlag();
    this->continent = country.getContinent();
    this->capital = country.getCapital();
    this->popularThings = country.getPopularThings();
    this->languages = country.getLanguages();
    this->currencies = country.getCurrencies();
    this->coordinates = country.getCoordinates();
    return *this;
}

Country::~Country() {
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

void Country::setContinent(const string &continent) {
    this->continent = continent;
}

string Country::getContinent() const {
    return continent;
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

void Country::setFlag(const string &flag) {
    this->flag = flag;
}

string Country::getFlag() const {
    return flag;
}

void Country::setPopularThings(const vector<string> &popularThings) {
    this->popularThings = popularThings;
}

const vector<string> Country::getPopularThings() const {
    return popularThings;
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

void Country::setCoordinates(const GeoCoordinates& coordinates) {
    this->coordinates = coordinates;
}

GeoCoordinates Country::getCoordinates() const {
    return coordinates;
}

bool operator==(const Country& leftHandCountry, const Country& rightHandCountry) {
    return leftHandCountry.getID() == rightHandCountry.getID();
}
