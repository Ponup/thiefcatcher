#include "SquareButton.h"

SquareButton::SquareButton(SDL_Renderer* renderer, const char* image, const char* imageOver, const Point& position, const string& label) :
	image(new Texture(renderer, image)),
	imageOver(new Texture(renderer, imageOver)),
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

Texture* SquareButton::getImage() {
	return image;
}

Texture* SquareButton::getImageOver() {
	return imageOver;
}
