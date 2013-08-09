#include "Particle.h"

Particle::Particle() {
}

Particle::~Particle() {
	
}

void Particle::setPosition(const Point &position) {
	this->position = position;
}

Point Particle::getPosition() const {
	return position;
}

