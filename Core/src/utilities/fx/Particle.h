#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <Surface.h>

class Particle {
protected:
	Point position;
	
public:
	Particle();
	virtual ~Particle();

	void setPosition(const Point &position);
	Point getPosition() const;
	
	virtual bool isDead() = 0;

	virtual void update() = 0;
	virtual void draw(Surface *surface) = 0;
};

#endif /*PARTICLE_H_*/
