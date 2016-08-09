#include "PlacesManager.h"

#include <Database.h>
using Kangaroo::Database;

#include <ResultSet.h>

vector<Place> PlacesManager::findRandom(unsigned int limit) {
	vector<Place> places;

	ResultSet &rs = Database::getInstance().execute("SELECT id, name FROM place ORDER BY RANDOM() LIMIT %d", limit);
	while (rs.hasNext()) {
		Place place;
		place.setId(rs.getInt(0));
		place.setName(rs.getString(1));
		places.push_back(place);
	}

	return places;
}

