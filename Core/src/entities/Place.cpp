#include "Place.h"

Place::Place() {
}

Place::~Place() {
}

void Place::setId(unsigned char id) {
	this->id = id;
}

unsigned char Place::getId() const {
	return id;
}

void Place::setName( const string &name ) {
	this->name = name;
}

string Place::getName() const {
	return name;
}

Surface* Place::getSurface() const {
	string path = "resources/images/places/" + name + ".png";
	return new Surface(path.c_str(), true);
}

Surface* Place::getCharacterSurface() const {
	string path = "resources/images/places/" + name + "_character.png";
	return new Surface(path.c_str());
}
