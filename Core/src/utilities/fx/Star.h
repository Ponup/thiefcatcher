#ifndef STAR_H_
#define STAR_H_

#include <Surface.h>
#include "Particle.h"
#include "utilities/RandomGen.h"

class Star : public Particle {
private:
	Surface * starSurface;
public:
	Star();
	virtual ~Star();
	
	void update();
	void draw(Surface * surface);
};

#endif /*STAR_H_*/
