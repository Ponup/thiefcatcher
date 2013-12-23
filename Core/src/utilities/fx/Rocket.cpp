#include "Rocket.h"

#include <math.h>
#include <SDL_gfxPrimitives.h>

#include "Particle.h"
#include "utilities/RandomGen.h"

Rocket::Rocket(int velIniX_, int velIniY_, int angle_) :
	velIniX(velIniX_), velIniY(velIniY_), angle(angle_) {
	
	v_y = 0;
	t = 0;
}

Rocket::~Rocket() {

}

void Rocket::setColor(const Color &color) {
	this->color = color;
}

bool Rocket::isDead() {
	return ( t > 0 && position.getY() > 700 );
}

void Rocket::update() {
	float rad = (angle * M_PI) / 180;

	float v_x = velIniX * cos(rad);
	v_y = velIniY * sin(rad) - 9.8 * t;

	float x = initialPos.getX() + v_x * t;
	float y = initialPos.getY() - (v_y * t - 0.5 * 9.8 * pow(t, 2));

	t += 0.1;

	setPosition(Point(x, y));
}

void Rocket::draw(Surface *surface) {
	Uint32 c = color.toSDL(surface->toSDL());
	filledCircleColor(surface->toSDL(), position.getX(), position.getY(), t/0.5, c);
}

