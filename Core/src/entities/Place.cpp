#include "Place.h"

Place::Place() : visited{false} {
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
