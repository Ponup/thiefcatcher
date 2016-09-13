#pragma once

#include <Point.h>
#include <Dimension.h>
#include <Area.h>
#include <Text.h>

class MenuItem {

	Point position;
	Area area;
	Text text;

public:
	MenuItem() {}
	void setArea(const Area &area);

	void setText(const Text& text);
	Text getText() const;

	void setPosition(const Point& position);
	const Point &getPosition() const;
};
