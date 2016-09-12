#pragma once

#include <Texture.h>
#include <Point.h>

using Kangaroo::Texture;

class SquareButton {

	Texture* image;
	Texture* imageOver;
	Point position;
	string label;

public:
	SquareButton(SDL_Renderer* renderer, const char *image, const char *imageOver, const Point& position, const string& label);
	~SquareButton();

	string getLabel();
	Point getPosition();
	Texture* getImage();
	Texture* getImageOver();
};
