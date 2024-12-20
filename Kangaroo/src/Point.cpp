#include "Point.h"

const Point Point::Origin(0, 0);

Point Point::operator-(const Point& point) {
    return Point(x - point.x, y - point.y);
}

Point Point::operator+(const Point &point) {
    return Point(x + point.x, y + point.y);
}

Point Point::operator=(const Point &point) {
    x = point.x;
    y = point.y;
    return *this;
}

bool Point::operator==(const Point &point) {
    return ( x == point.x && y == point.y);
}

ostream& operator<<(ostream& stream, const Point& point) {
	return stream << "Point {x: " << point.x << ", y: " << point.y << "}";
}

