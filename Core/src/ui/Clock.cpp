#include "Clock.h"

#include <math.h>
#include <SDL2/SDL2_gfxPrimitives.h>

Clock::Clock() {
	clockSurf.load("resources/images/game/clock_small.png", true);
}

Clock::~Clock() {
}

void Clock::setPosition(const Point &position) {
	this->position = position;
}

void Clock::draw(const DateTime &dateTime, Surface *screen) {
	// angle = 30 * (3-3) = -90 - 90º = 0
	// angle = 30 * (6-3) = -180 - 90º = 90
	// angle = 30 * (9-3) = -270 - 90 =
	// angle = 30 * (12-3) = 

	screen->drawSurface(&clockSurf, position);
/*
	int angle = 30 * dateTime.getHour();
	
	float rad = ((angle - 90) * M_PI) / 180;

	int radio = 42.5;

	int x = cos(-rad) * radio;
	int y = sin(-rad) * radio;

	int xx = position.x + radio;
	int yy = position.y + radio;

	aalineRGBA(screen->toSDL(), xx, yy, xx + x, yy - y, 0, 0, 0, 255);
	screen->updateArea(Area(position, clockSurf.getDimension()));
*/
}

