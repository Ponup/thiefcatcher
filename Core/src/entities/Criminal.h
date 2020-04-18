#pragma once

#include <string>
using std::string;

#include "entities/Genre.h"

class Criminal {
    int id;
    string name;
    Genre genre;
    string build;
    string hair;
    string feature;
    string complexion; // Appearance of person's skin

public:
    Criminal();
    ~Criminal();

    void setID(int id);
    int getID() const;

    void setName(const string &name);
    string getName() const;

    void setGenre(Genre genre);
    Genre getGenre() const;

    void setBuild(const string& build);
    string getBuild() const;

    void setHair(const string &hair);
    string getHair() const;

    void setFeature(const string &feature);
    string getFeature() const;

    void setComplexion(const string& complexion);
    string getComplexion() const;
};
