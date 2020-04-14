#include "Criminal.h"

#include "entities/format/CriminalFormatter.h"

#include <sstream>
using std::ostringstream;

Criminal::Criminal() {
    id = -1;
    genre = Genre::Female;
}

Criminal::~Criminal() {
}

void Criminal::setID(int id) {
    this->id = id;
}

int Criminal::getID() const {
    return id;
}

void Criminal::setName(const string &name) {
    this->name = name;
}

string Criminal::getName() const {
    return name;
}

void Criminal::setGenre(Genre genre) {
    this->genre = genre;
}

Genre Criminal::getGenre() const {
    return genre;
}

void Criminal::setHair(const string &hair) {
    this->hair = hair;
}

string Criminal::getHair() const {
    return hair;
}

void Criminal::setBuild(const string& build) {
    this->build = build;
}

string Criminal::getBuild() const {
    return build;
}

void Criminal::setFeature(const string &feature) {
    this->feature = feature;
}

string Criminal::getFeature() const {
    return feature;
}

void Criminal::setComplexion(const string& complexion) {
    this->complexion = complexion;
}

string Criminal::getComplexion() const {
    return complexion;
}

