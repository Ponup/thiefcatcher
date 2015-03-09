#pragma once

#include <vector>
using std::vector;

#include "Place.h"

class PlacesManager {
	public:
		static vector<Place> findRandom( int limit );
};
