#include "MenuItem.h"

void MenuItem::setArea(const Area &area) {
	this->area = area;
}

void MenuItem::setText(const Text& text) {
	this->text = text;
}

Text MenuItem::getText() const {
	return text;
}

void MenuItem::setPosition(const Point& position) {
	this->position = position;
}

const Point &MenuItem::getPosition() const {
	return position;
}

