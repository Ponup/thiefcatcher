#pragma once

#include "Surface.h"
#include "Point.h"

class SquareButton {

	Surface* image;
	Surface* imageOver;
	Point position;
	string label;

public:
	SquareButton(const char *image, const char *imageOver, const Point& position, const string& label);
	~SquareButton();

	string getLabel();
	Point getPosition();
	Surface* getImage();
	Surface* getImageOver();
};
