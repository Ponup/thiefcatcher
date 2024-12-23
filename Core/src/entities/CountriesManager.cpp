#include "CountriesManager.h"

#include <tinyxml2.h>
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using tinyxml2::XMLError;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <stdlib.h>

#include <algorithm>
using std::shuffle;
#include <random>

vector<Country> CountriesManager::findAll() {
    static vector<Country> countries;

    if (!countries.empty()) {
        return countries;
    }

    XMLDocument xmlDoc;
    XMLError errorCode = xmlDoc.LoadFile("data/countries.xml");
    if (tinyxml2::XML_SUCCESS != errorCode) {
        return countries;
    }

    unsigned int id = 0;
    XMLElement *rootNode = xmlDoc.RootElement();
    for (XMLElement *countryNode = rootNode->FirstChildElement("country"); nullptr != countryNode; countryNode = countryNode->NextSiblingElement("country")) {
        Country country;
        country.setID(++id);
        country.setCode(countryNode->Attribute("code"));
        country.setIsoCode(countryNode->Attribute("isocode"));
        country.setName(countryNode->FirstChildElement("name")->GetText());
        country.setCapital(countryNode->FirstChildElement("capital")->GetText());
        country.setContinent(countryNode->FirstChildElement("continent")->GetText());
        country.setFlag(countryNode->FirstChildElement("flag")->GetText());

        GeoCoordinates coordinates = {
            atof(countryNode->FirstChildElement("coordinates")->Attribute("lat")),
            atof(countryNode->FirstChildElement("coordinates")->Attribute("long"))
        };
        country.setCoordinates(coordinates);

        vector<string> popularThings;
        XMLElement *popularThingsNodes = countryNode->FirstChildElement("popular-things");
        for (XMLElement *thingNode = popularThingsNodes->FirstChildElement("thing"); thingNode != nullptr; thingNode = thingNode->NextSiblingElement("thing")) {
            popularThings.push_back(thingNode->GetText());
        }
        country.setPopularThings(popularThings);

        vector<string> languages;
        XMLElement *languagesNode = countryNode->FirstChildElement("languages");
        for (XMLElement *languageNode = languagesNode->FirstChildElement("language"); languageNode != nullptr; languageNode = languageNode->NextSiblingElement("language")) {
            languages.push_back(languageNode->GetText());
        }
        country.setLanguages(languages);

        vector<string> currencies;
        XMLElement *currenciesNode = countryNode->FirstChildElement("currencies");
        for (XMLElement *currencyNode = currenciesNode->FirstChildElement("currency"); currencyNode != nullptr; currencyNode = currencyNode->NextSiblingElement("currency")) {
            currencies.push_back(currencyNode->GetText());
        }
        country.setCurrencies(currencies);

        countries.push_back(country);
    }

    return countries;
}

Country CountriesManager::findByPrimaryKey(unsigned int id) {
    vector<Country> countries = findAll();
    return countries.at(id - 1);
}

vector<Country> CountriesManager::findRandom(int limit) {
    vector<Country> countries = findAll();
    std::mt19937 rng(std::time(nullptr));
    std::ranges::shuffle(countries, rng);
    return vector<Country>(countries.begin(), countries.begin() + limit);
}
