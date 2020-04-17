#pragma once

#include "utilities/DateTime.h"

#include <Renderer.h>
using Kangaroo::Renderer;

#include <Texture.h>
using Kangaroo::Texture;

#include <Point.h>

class Clock
{
	Renderer *renderer;
	Texture faceTexture;
	Point position;

	void drawHand(int angle, int radio, const Color &color);

public:
	Clock(Renderer *renderer, const Point &position);
	~Clock();

	void draw(const DateTime &dateTime);
};
