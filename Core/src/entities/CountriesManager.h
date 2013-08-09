#ifndef COUNTRIESMANAGER_H
#define COUNTRIESMANAGER_H

#include <vector>
using std::vector;

#include <Database.h>
#include <ResultSet.h>

#include "Country.h"

class CountriesManager {

private:
	static void completeCountry(Country *country, const ResultSet &rs, int index);
		
public:
	static vector<Country> findAll();
	static vector<int> findAllPrimaryKeys();
	static Country *findByPrimaryKey(int id);
};

#endif
