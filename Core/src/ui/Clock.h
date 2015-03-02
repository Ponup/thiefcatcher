#ifndef CLOCK_H
#define CLOCK_H

#include <Point.h>
#include <Surface.h>
#include <Window.h>

#include "utilities/DateTime.h"

class Clock {
	
private:
	Point position;
	Surface clockSurf;
	Window *window;

public:
	Clock(Window *window);
	~Clock();
	
	void setPosition(const Point &position);
	void draw(const DateTime &dateTime, Surface *screen);
};

#endif
