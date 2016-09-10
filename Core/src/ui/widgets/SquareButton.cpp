#include "SquareButton.h"

SquareButton::SquareButton(const char* image, const char* imageOver, const Point& position, const string& label) :
	image(new Surface(image)),
	imageOver(new Surface(imageOver)),
	position(position),
	label(label)
	{
	}

SquareButton::~SquareButton() {
	if (image != nullptr)
		delete image;
	if (imageOver != nullptr)
		delete imageOver;
}

string SquareButton::getLabel() {
	return label;
}

Point SquareButton::getPosition() {
	return position;
}

Surface* SquareButton::getImage() {
	return image;
}

Surface* SquareButton::getImageOver() {
	return imageOver;
}
