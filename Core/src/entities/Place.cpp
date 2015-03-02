#include "Place.h"

#include <Dimension.h>
#include <Point.h>

Place::Place() {
	name = NULL;
}

Place::Place(const Place &place) {
	this->id = place.getId();
	this->name = strdup(place.getName());
}

Place & Place::operator=(const Place &place) {
	this->id = place.getId();
	this->name = strdup(place.getName());
	return *this;
}

Place::~Place() {
	if(name) free(name);
	name = NULL;
}

void Place::setId(unsigned char id) {
	this->id = id;
}

unsigned char Place::getId() const {
	return id;
}

void Place::setName(const char *name) {
	this->name = strdup(name);
}

const char *Place::getName() const {
	return strdup(name);
}

Surface *Place::getSurface() const {
	char path[100];
	memset(path, '\0', 100);
	sprintf(path, "resources/images/places/%s.png", name);
	
	return new Surface(path, true);
}

Surface *Place::getCharacterSurface() const {
	char path[100];
	memset(path, '\0', 100);
	sprintf(path, "resources/images/places/%s_character.png", name);
	
	return new Surface(path);
}

