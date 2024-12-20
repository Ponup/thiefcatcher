#pragma once

#include <utility>
using std::pair;

#include <vector>
using std::vector;

#include <cmath>

#include "Point.h"

class MathUtil {
	
public:
	static inline float degree2radian( float degree ) {
		return ( degree * M_PI / 180 );
	}

	static inline float radian2degree( float radian ) {
		return ( radian * ( 180 / M_PI ) );
	}

	static float calculateDistance(const Point &a, const Point &b);
	static double calculateDistance( pair<double, double> a, pair<double, double> b );
	static double calculateDegrees(const Point &a, const Point &b);
	static double calculateDegrees( pair<double, double> a, pair<double, double> b );
	static vector<Point> calculatePath( const Point& a, const Point& b );
	static vector<Point> calculatePath( pair<double, double> a, pair<double, double> b );
};

