#include "CriminalsManager.h"

void CriminalsManager::completeCriminal(ResultSet &rs, Criminal *criminal, int i) {
	criminal->setID(rs.getInt(i, 0));
	criminal->setName(rs.getString(i, 1));
	criminal->setSex(rs.getString(i, 2));
	criminal->setHobby(rs.getString(i, 3));
	criminal->setHair(rs.getString(i, 4));
	criminal->setFeature(rs.getString(i, 5));
}

vector<Criminal> CriminalsManager::findAll() {
	vector<Criminal> criminals;

	ResultSet &rs = Database::getInstance().execute("SELECT id, name, genre, hobby, hair, feature FROM criminal");
	for(unsigned int i = 0; i < rs.rowsCount(); i++) {
		Criminal criminal;
		completeCriminal(rs, &criminal, i);
		criminals.push_back(criminal);
	}

	return criminals;	
}

vector<string> &CriminalsManager::findAllHairs() {
	vector<string> *list = new vector<string>;

	ResultSet &rs = Database::getInstance().execute("SELECT DISTINCT hair FROM criminal ORDER BY hair ASC");
	for(unsigned int i = 0; i < rs.rowsCount(); i++) {
		list->push_back(rs.getString(i, 0));
	}

	return *list;		
}

vector<string> & CriminalsManager::findAllHobbies() {
	vector<string> *list = new vector<string>;

	ResultSet &rs = Database::getInstance().execute("SELECT DISTINCT hobby FROM criminal ORDER BY hobby ASC");
	for(unsigned int i = 0; i < rs.rowsCount(); i++) {
		list->push_back(rs.getString(i, 0));
	}

	return *list;			
}

vector<string> &CriminalsManager::findAllFeatures() {	
	vector<string> *list = new vector<string>;

	ResultSet &rs = Database::getInstance().execute("SELECT DISTINCT feature FROM criminal ORDER BY feature ASC");
	for(unsigned int i = 0; i < rs.rowsCount(); i++) {
		list->push_back(rs.getString(i, 0));
	}

	return *list;
}

Criminal *CriminalsManager::findByFeatures(const char *genre, const char *hobby, const char *hair) {
	Criminal *criminal = NULL;
	
	ResultSet & rs = Database::getInstance().execute("SELECT * FROM criminal WHERE genre = '%s' AND hobby = '%s' AND hair = '%s'",
			genre, hobby, hair
	);
	if(rs.rowsCount() == 1) {
		criminal = new Criminal;
		completeCriminal(rs, criminal, 0);
	}
	
	return criminal;
}

vector<int> CriminalsManager::findAllPrimaryKeys() {
	vector<int> primaryKeys;

	ResultSet &rs = Database::getInstance().execute("SELECT id FROM criminal");
	for(unsigned int i = 0; i < rs.rowsCount(); i++) {
		primaryKeys.push_back(rs.getInt(i, 0));
	}

	return primaryKeys;	
}

Criminal *CriminalsManager::findByPrimaryKey(int id) {
	Criminal *criminal = NULL;

	ResultSet &rs = Database::getInstance().execute("SELECT id, name, genre, hobby, hair, feature FROM criminal WHERE id = %d", id);
	if(rs.rowsCount() == 1) {
		criminal = new Criminal;
		completeCriminal(rs, criminal, 0);
	}

	return criminal;
}

