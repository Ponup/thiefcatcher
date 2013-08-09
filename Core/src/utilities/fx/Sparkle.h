#ifndef SPARKLE_H
#define SPARKLE_H

#include <stdio.h>
#include <Point.h>
#include <Color.h>
#include <Surface.h>
#include <SDL_gfxPrimitives.h>

#include "Particle.h"
#include "utilities/RandomGen.h"

class Sparkle : public Particle {
private:
	Color color;
	int size;
	int life;
	
public:
	Sparkle(int duration);
	virtual ~Sparkle();

	void update();
	void draw(Surface * surface);
};

#endif
