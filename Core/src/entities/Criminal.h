#pragma once

#include <string>
using std::string;

enum class Genre {
    Female = 0,
    Male
};

class Criminal {
    int id;
    string name;
    Genre genre;
    string hairColor;
    string hairLength;
    string build;
    string eyesColor;
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

    void setHairColor(const string &hair);
    string getHairColor() const;

    void setHairLength(const string &hairLength);
    string getHairLength() const;

    void setBuild(const string& build);
    string getBuild() const;

    void setEyesColor(const string& eyesColor);
    string getEyesColor() const;

    void setFeature(const string &feature);
    string getFeature() const;

    void setComplexion(const string& complexion);
    string getComplexion() const;
};

