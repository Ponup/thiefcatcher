#ifndef CLOCK_H
#define CLOCK_H

#include <Point.h>
#include <Surface.h>

#include "utilities/DateTime.h"

class Clock {
	
private:
	Point position;
	Surface clockSurf;

public:
	Clock();
	~Clock();
	
	void setPosition(const Point &position);
	void draw(const DateTime &dateTime, Surface *screen);
};

#endif
