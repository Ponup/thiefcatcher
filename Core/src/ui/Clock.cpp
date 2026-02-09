#include "Clock.h"

#include <math.h>

Clock::Clock(Renderer *renderer, const Point &position) : renderer{renderer},
														  faceTexture{renderer->internal, "resources/images/game/clock_small.png"},
														  position{position},
														  drawSecondHand{false}
{
}

Clock::~Clock()
{
}

void Clock::draw(const DateTime &dateTime)
{
	renderer->drawTexture(&faceTexture, position);

	// Hour hand
	drawHand(dateTime.getHour() * 30, 40, Color(0, 0, 0));
	if (drawSecondHand)
	{
		// Seconds hand
		drawHand(dateTime.getSeconds() * 6, 25, Color(0xff, 0, 0));
	}
}

void Clock::drawHand(int angle, int radio, const Color &color)
{
	float rad = ((angle - 90) * M_PI) / 180;

	int x = cos(-rad) * radio;
	int y = sin(-rad) * radio;

	int xx = position.x + (faceTexture.getWidth() >> 1);
	int yy = position.y + (faceTexture.getHeight() >> 1);

	(void)x;
	(void)y;
	(void)xx;
	(void)yy;
	(void)color;

	// @todo replace with shader
	// aalineRGBA(renderer->internal, xx, yy, xx + x, yy - y, color.r, color.g, color.b, color.a);
}
