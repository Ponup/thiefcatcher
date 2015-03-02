#include "Sprite.h"

Sprite::Sprite(const char *fileName, const int numFrames_, const Dimension &frameDim_)
	: numFrames(numFrames_), frameDim(frameDim_) {
	currentFrame = 0;
	position = Point::Origin;
	
	frames = new Surface*[numFrames];

	//Surface *surface = new Surface(fileName);
	for(int i = 0; i <= numFrames; i++) {
		char path[100];
		memset(path, '\0', 100);
		sprintf(path, fileName, i);
		//frames[i] = surface->getArea(Point(i * frameDim.getWidth(), 0), frameDim);
		frames[i] = new Surface(path);
	}	
	//delete surface;
}

Sprite::~Sprite() {
	delete *frames;
}

void Sprite::setPosition(const Point &position_) {
	position = position_;
}

void Sprite::update(Surface *screen) {
	screen->updateArea(position, frameDim);
}

void Sprite::draw(Surface *screen) {
	screen->drawSurface(frames[currentFrame], position);

	currentFrame++;
	if(currentFrame > numFrames) currentFrame = 0;
}

