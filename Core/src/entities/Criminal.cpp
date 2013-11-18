#include "Criminal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entities/format/CriminalFormatter.h"

Criminal::Criminal() {
	id = -1;
}

Criminal::~Criminal() {
}

void Criminal::setID(int id) {
	this->id = id;
}

int Criminal::getID() const {
	return id;
}

void Criminal::setName(const char *name) {
	this->name = strdup(name);
}

const char *Criminal::getName() const {
	return strdup(name);
}

void Criminal::setGenre( Genre genre ) {
	this->genre = genre;
}

Genre Criminal::getGenre() const {
	return genre;
}

void Criminal::setHobby(const char *hobby) {
	this->hobby = strdup(hobby);
}

const char *Criminal::getHobby() const {
	return hobby;
}

void Criminal::setHair(const char *hair) {
	this->hair = strdup(hair);
}

const char *Criminal::getHair() const {
	return hair;
}

void Criminal::setFeature(const char *feature) {
	this->feature = strdup(feature);
}

const char *Criminal::getFeature() const {
	return feature;
}

const char *Criminal::toString() const {
	char *text = (char *)calloc(200, sizeof(char));
	if(!text) return NULL;

	sprintf(text, "name: %s, sex: %s, hobby: %s, hair: %s, feature: %s",
		name, CriminalFormatter::formatGenre( genre ), hobby, hair, feature
	);

	return text;
}

