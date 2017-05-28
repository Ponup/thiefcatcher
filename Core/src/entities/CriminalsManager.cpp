#include "CriminalsManager.h"

#include <tinyxml2.h>

using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using tinyxml2::XMLError;

#include <iostream>
using std::cerr;
using std::endl;

vector<Criminal>& CriminalsManager::findAll() {
    static vector<Criminal> criminals;
    if (!criminals.empty()) {
        return criminals;
    }

    XMLDocument doc;
    XMLError errorCode = doc.LoadFile("data/criminals.xml");
    if (errorCode != tinyxml2::XML_NO_ERROR) {
        cerr << "XML error code: " << errorCode << endl;
        return criminals;
    }

    unsigned int criminalId = 0;
    XMLElement *rootNode = doc.RootElement();
    for (XMLElement *criminalNode = rootNode->FirstChildElement("criminal"); nullptr != criminalNode; criminalNode = criminalNode->NextSiblingElement("criminal")) {
        Criminal criminal;
        criminal.setID(++criminalId);
        criminal.setGenre(strncasecmp("male", criminalNode->Attribute("genre"), 4) == 0 ? Genre::Male : Genre::Female);
        criminal.setName(criminalNode->FirstChildElement("name")->GetText());
        criminal.setBuild(criminalNode->FirstChildElement("build")->GetText());
        criminal.setHairColor(criminalNode->FirstChildElement("hair")->GetText());
        criminal.setFeature(criminalNode->FirstChildElement("body")->GetText());
        criminals.push_back(criminal);
    }

    return criminals;
}

vector<string> &CriminalsManager::findAllHairs() {
    vector<string> *list = new vector<string>;

    vector<Criminal> criminals = findAll();
    for (vector<Criminal>::iterator it = criminals.begin(); it != criminals.end(); ++it) {
        Criminal criminal = *it;
        list->push_back(criminal.getHairColor());
    }

    return *list;
}

vector<string> & CriminalsManager::findAllHobbies() {
    vector<string> *list = new vector<string>;

    vector<Criminal> criminals = findAll();
    for (vector<Criminal>::iterator it = criminals.begin(); it != criminals.end(); ++it) {
        Criminal criminal = *it;
        list->push_back(criminal.getBuild());
    }

    return *list;
}

vector<string> &CriminalsManager::findAllFeatures() {
    vector<string> *list = new vector<string>;

    vector<Criminal> criminals = findAll();
    for (vector<Criminal>::iterator it = criminals.begin(); it != criminals.end(); ++it) {
        Criminal criminal = *it;
        list->push_back(criminal.getFeature());
    }

    return *list;
}

Criminal *CriminalsManager::findByFeatures(Genre genre, const string &build, const string &hairColor) {
    vector<Criminal> criminals = findAll();
    for (vector<Criminal>::iterator it = criminals.begin(); it != criminals.end(); ++it) {
        Criminal criminal = *it;
        if (genre == criminal.getGenre() && criminal.getBuild() == build && criminal.getHairColor() == hairColor) {
            return new Criminal(criminal);
        }
    }

    return nullptr;
}

vector<int> CriminalsManager::findAllPrimaryKeys() {
    vector<int> primaryKeys;

    vector<Criminal> criminals = findAll();
    for (vector<Criminal>::iterator it = criminals.begin(); it != criminals.end(); ++it) {
        Criminal criminal = *it;
        primaryKeys.push_back(criminal.getID());
    }

    return primaryKeys;
}

Criminal *CriminalsManager::findByPrimaryKey(unsigned int id) {
    vector<Criminal> criminals = findAll();
    return ( id - 1 < criminals.size() ? new Criminal(criminals.at(id - 1)) : nullptr);
}

