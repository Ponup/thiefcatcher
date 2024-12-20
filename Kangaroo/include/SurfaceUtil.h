#pragma once

#include "Surface.h"
#include "Point.h"

class SurfaceUtil {

public:
	static Point drawCentered(Surface *surface, Surface *parent);
	static Point getCentered(Surface *surface, Surface *parent);
	
	static bool fadeIn(Surface *surface, Surface *parent, const Point &to);
	static bool fadeOut(Surface *surface, Surface *parent, const Point &to);
};

