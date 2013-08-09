#include "Criminal.h"

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

void Criminal::setSex(const char *sex) {
	this->sex = strdup(sex);
}

const char *Criminal::getSex() const {
	return sex;
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
		name, sex, hobby, hair, feature
	);

	return text;
}

