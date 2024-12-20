#pragma once

#include <SDL.h>

#include <iostream>
using std::ostream;

#include "Point.h"
#include "Dimension.h"

/**
 * Contains information about a region, indicated by a dimension (width, height), and its position.
 * 
 * @see Point
 * @see Dimension
 */
class Area : public SDL_Rect {

public:
	Area() { }
	Area(unsigned int x_, unsigned int y_, unsigned int width, unsigned int height) { x = x_; y = y_; w = width; h = height; }
	Area(const Point &point_, const Dimension &dimension_) { x = point_.x; y = point_.y; w = dimension_.w; h = dimension_.h; }

	void setPoint(const Point &point);
	Point getPoint() const;

	void setDimension(const Dimension &dimension);
	Dimension getDimension() const;
	
	bool contains(short x, short y) const;
};

ostream& operator<<(ostream& stream, const Area& area);

