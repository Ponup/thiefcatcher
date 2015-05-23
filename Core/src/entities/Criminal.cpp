#include "Criminal.h"

#include "entities/format/CriminalFormatter.h"

#include <sstream>
using std::stringstream;

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

void Criminal::setName(const string &name) {
	this->name = name;
}

string Criminal::getName() const {
	return name;
}

void Criminal::setGenre( Genre genre ) {
	this->genre = genre;
}

Genre Criminal::getGenre() const {
	return genre;
}

void Criminal::setHobby(const string &hobby) {
	this->hobby = hobby;
}

string Criminal::getHobby() const {
	return hobby;
}

void Criminal::setHair(const string &hair) {
	this->hair = hair;
}

string Criminal::getHair() const {
	return hair;
}

void Criminal::setFeature(const string &feature) {
	this->feature = feature;
}

string Criminal::getFeature() const {
	return feature;
}

string Criminal::toString() const {
	stringstream text;
	text << "name: " << name << ", genre: " << CriminalFormatter::formatGenre( genre ) << ", hobby: " << hobby << ", hair: " << hair << ", feature: " << feature;

	return text.str();
}

