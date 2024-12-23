#pragma once

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <Surface.h>
#include <Point.h>

typedef unsigned char CountryId;

#include "GeoCoordinates.h"

class Country {

    CountryId id;
    string isoCode;
    string code;
    string name;
    string continent;
    string capital;
    string flag;
    vector<string> popularThings;
    GeoCoordinates coordinates;
    vector<string> languages;
    vector<string> currencies;

public:
    Country();
    Country(const Country& country);
    Country &operator=(const Country& country);
    ~Country();

    void setIsoCode(const string &isoCode);
    string getIsoCode() const;
    void setCode(const string &code);
    string getCode() const;
    void setID(CountryId id);
    CountryId getID() const;
    void setName(const string &name);
    string getName() const;
    void setContinent(const string &description);
    string getContinent() const;
    void setCapital(const string &treasure);
    string getCapital() const;
    void setFlag(const string &flag);
    string getFlag() const;
    void setPopularThings(const vector<string> &popularThings);
    const vector<string> getPopularThings() const;
    void setLanguages(const vector<string> &languages);
    const vector<string> getLanguages() const;
    void setCurrencies(const vector<string> &currencies);
    const vector<string> getCurrencies() const;
    string getFirstCurrency() const;
    void setCoordinates(const GeoCoordinates& coordinates);
    GeoCoordinates getCoordinates() const;
};

bool operator==(const Country& leftHandCountry, const Country& rightHandCountry);
