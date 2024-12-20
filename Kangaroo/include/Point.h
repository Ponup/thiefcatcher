#pragma once

#include <SDL_rect.h>

#include <iostream>
using std::ostream;

/**
 * Indicates the position of an element on a 2D space.
 */
class Point : public SDL_Point {
public:
    const static Point Origin;

    Point() {
        x = y = 0;
    }

    Point(const Point& point) {
        x = point.x;
        y = point.y;
    }

    Point(short x, short y) {
        this->x = x;
        this->y = y;
    }

    Point operator-(const Point& point);
    Point operator+(const Point& point);
    Point operator=(const Point& point);
    bool operator==(const Point& point);
};

ostream& operator<<(ostream& stream, const Point& point);

