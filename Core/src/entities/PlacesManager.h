#ifndef PLACESMANAGER_H
#define PLACESMANAGER_H 1

#include <vector>
#include <Database.h>
#include <ResultSet.h>
#include "Place.h"

using std::vector;

class PlacesManager {
	public:
		static Place & findByPrimaryKey(int id);
		static vector<int> findAllPrimaryKeys();
};

#endif
