#ifndef ISPRITE_H
#define ISPRITE_H

#include <Surface.h>

class ISprite {
	
public:
	virtual void update() = 0;
	virtual void draw(Surface *surface) = 0;
};

#endif
