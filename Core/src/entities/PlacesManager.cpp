#include "PlacesManager.h"

Place & PlacesManager::findByPrimaryKey(int id) {
	Place * place = new Place();

	ResultSet & rs = Database::getInstance().execute("SELECT id, name FROM place WHERE id = %d", id);
	if(rs.rowsCount() == 1) {
		place->setId(rs.getInt(0, 0));
		place->setName(rs.getString(0, 1));
	}

	return * place;
}

vector<int> PlacesManager::findAllPrimaryKeys() {
	vector<int> primaryKeys;

	ResultSet & rs = Database::getInstance().execute("SELECT id FROM place");
	for(unsigned int i = 0; i < rs.rowsCount(); i++) {
		primaryKeys.push_back(rs.getInt(i, 0));
	}

	return primaryKeys;	
}
