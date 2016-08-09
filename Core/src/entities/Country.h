#ifndef COUNTRY_H
#define COUNTRY_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <utility>
using std::pair;

#include <Surface.h>
#include <Point.h>

class Country {
private:
    unsigned char id;
    string isoCode;
    string code;
    string name;
    string description;
    string treasure;
    string flagDesc;
    string capital;

    double latitude, longitude;

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
    void setID(unsigned char id);
    unsigned char getID() const;
    void setName(const string &name);
    string getName() const;
    void setDescription(const string &description);
    string getDescription() const;
    void setTreasure(const string &treasure);
    string getTreasure() const;
    void setFlagDescription(const string &flagDesc);
    string getFlagDescription() const;
    void setLanguages(const vector<string> &languages);
    const vector<string> getLanguages() const;
    void setCurrencies(const vector<string> &currencies);
    const vector<string> getCurrencies() const;
    string getFirstCurrency(void) const;
    void setCapital(const string &capital);
    string getCapital() const;

    void setLatitude(double latitude);
    double getLatitude() const;
    void setLongitude(double longitude);
    double getLongitude() const;
    pair<double, double> getLatitudeLongitude() const;

    Surface* getPhoto() const;
    Surface* getFlag() const;

    string toString() const;
};

#endif

