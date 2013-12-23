#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {
}

ParticleSystem::~ParticleSystem() {
//	for(unsigned char i = particles.size() - 1; i >= 0; i--) {
//		//particles.erase(particles.begin() + i);
//	}
}

void ParticleSystem::addParticle(Particle *particle) {
	particles.push_back(particle);
}

unsigned int ParticleSystem::getNumber() const {
	return particles.size();
}

void ParticleSystem::update() {
	for (unsigned int i = 0; i < particles.size(); i++) {
		Particle *particle = particles[i];
		particle->update();
		if(particle->isDead()) {
			particles.erase(particles.begin() + i);
			onParticleDie();
		}
	}
}

void ParticleSystem::draw(Surface *surface) {
	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i]->draw(surface);
	}
}

