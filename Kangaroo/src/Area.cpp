#include "Area.h"

void Area::setPoint(const Point &point) {
	x = point.x;
	y = point.y;
}

Point Area::getPoint() const {
	return Point( x, y );
}

void Area::setDimension(const Dimension &dimension) {
	w = dimension.w;
	h = dimension.h;
}

Dimension Area::getDimension() const {
	return Dimension( w, h );
}

bool Area::contains( short x_, short y_ ) const {
	return x_ >= x &&
	       x_ <= x + w &&
	       y_ >= y &&
	       y_ <= y + h;
}

ostream& operator<<(ostream& stream, const Area& area) {
	return stream << "Area {x: " << area.x << ", y: " << area.y << ", w: " << area.w << ", h: " << area.h << "}";
}

