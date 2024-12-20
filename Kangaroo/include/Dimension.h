#pragma once

#include <iostream>
using std::ostream;

/**
 * Contains information about the size of an element.
 */
class Dimension {

public:
	unsigned short w;
	unsigned short h;

	Dimension() : w(0), h(0) {}
	Dimension(unsigned short w, unsigned short h) : w(w), h(h) {}
	//Dimension(const Dimension& dimension) : w(dimension.w), h(dimension.h) {}
};

ostream& operator<<(ostream& stream, const Dimension& dimension);

