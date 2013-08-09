#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
using std::vector;

#include <Surface.h>

#include "Particle.h"

class ParticleSystem {
	private:
		vector<Particle*> particles;
		
	public:
		ParticleSystem();
		virtual ~ParticleSystem();
		
		void addParticle(Particle *particle);
		virtual void onParticleDie() = 0;
		
		void update();
		void draw(Surface *surface);
};

#endif

