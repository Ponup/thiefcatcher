#include "CountriesManager.h"

void CountriesManager::completeCountry(Country *country, const ResultSet &rs, int index) {
	country->setID(rs.getInt(index, 0));
	country->setName(rs.getString(index, 1));
	country->setDescription(rs.getString(index, 2));
	country->setTreasure(rs.getString(index, 3));
	country->setCoord(Point(rs.getInt(index, 4), rs.getInt(index, 5)));
	country->setCoin(rs.getString(index, 6));
	country->setFlagDescription(rs.getString(index, 7));
}

vector<Country> CountriesManager::findAll() {
	vector<Country> countries;

	ResultSet &rs = Database::getInstance().execute("SELECT id, name, description, treasure, coord_x, coord_y, currency, flag_desc FROM country");
	for(unsigned int i = 0; i < rs.rowsCount(); i++) {
		Country country;
		completeCountry(&country, rs, i);
		countries.push_back(country);
	}

	return countries;	
}

vector<int> CountriesManager::findAllPrimaryKeys() {
	vector<int> primaryKeys;

	ResultSet &rs = Database::getInstance().execute("SELECT id FROM country");
	for(unsigned int i = 0; i < rs.rowsCount(); i++) {
		primaryKeys.push_back(rs.getInt(i, 0));
	}

	return primaryKeys;	
}

Country *CountriesManager::findByPrimaryKey(int id) {
	Country *country = NULL;
	ResultSet &rs = Database::getInstance().execute("SELECT id, name, description, treasure, coord_x, coord_y, currency, flag_desc FROM country WHERE id = %d", id);
	if(rs.rowsCount() == 1) {
		country = new Country;
		completeCountry(country, rs, 0);
	}
	return country;
}

