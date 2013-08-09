#ifndef ROCKET_H_
#define ROCKET_H_

#include <Color.h>
#include <Surface.h>
#include <Point.h>

#include "utilities/fx/Particle.h"

class Rocket : public Particle {

private:
	int velIniX;
	
	int velIniY;
	int velY;
	
	int angle;
	
	float v_y;
	float t;
	
	Color color;
		
	void update();
	void draw(Surface *surface);

public:
	Rocket(int velIniX_, int velIniY_, int angle_);
	virtual ~Rocket();
	
	void setColor(const Color &color);
	
	bool isDead();
	
	Point initialPos;	
};

#endif /*ROCKET_H_*/
