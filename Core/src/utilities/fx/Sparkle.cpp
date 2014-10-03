#include "Sparkle.h"

Sparkle::Sparkle(int life_) : life(life_) {
	size = RandomGen::nextInt(1, 4);
	color = Color(
			RandomGen::nextInt(1, 255),
			RandomGen::nextInt(1, 255),
			RandomGen::nextInt(1, 255));
}

Sparkle::~Sparkle() {
	printf("Deleting sparkle... GUAY!\n");
}

void Sparkle::update() {
	int x = position.x+RandomGen::nextInt(-1, 1);
	int y = position.y+1;
	position = (Point(x, y));
	life--;
}

void Sparkle::draw(Surface * surface) {
	if(life > 0) {
		filledCircleRGBA(surface->toSDL(), 
			position.x, 
			position.y, 
			size, 
			color.r, color.g, color.b, life);
	}
}

