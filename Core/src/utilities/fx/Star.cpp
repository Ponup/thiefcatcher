#include "Star.h"

Star::Star() {
	starSurface = new Surface("resources/images/cursor.png");
	srand(time(NULL));
}

Star::~Star() {
	delete starSurface;
}

void Star::update() {
	int x = RandomGen::nextInt(1, 640);
	int y = RandomGen::nextInt(1, 480);

	position = Point(x, y);
}

void Star::draw(Surface * surface) {
	surface->drawSurface(starSurface, position);
}
