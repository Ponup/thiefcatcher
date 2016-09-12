#pragma once

#include <Point.h>
#include <Window.h>

#include "utilities/DateTime.h"

#include <Texture.h>

using Kangaroo::Texture;

#include <Renderer.h>

using Kangaroo::Renderer;

class Clock {

private:
	Point position;
	Texture surface;
	Window *window;

public:

	Clock(Window *window);
	~Clock();

	void setPosition(const Point &position);
	void draw(const DateTime &dateTime, Renderer* renderer);
};
