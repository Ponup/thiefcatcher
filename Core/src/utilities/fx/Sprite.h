#ifndef SPRITE_H_
#define SPRITE_H_

#include <Surface.h>

class Sprite {
private:
	int currentFrame;

	Surface **frames;
	int numFrames;
	Dimension frameDim;
	Point position;
	
public:
			Sprite(const char *fileName, const int numFrames,
					const Dimension &frameDim);
	~Sprite();

	void setPosition(const Point &position);
	
	void update(Surface *screen);
	void draw(Surface *screen);
};

#endif
