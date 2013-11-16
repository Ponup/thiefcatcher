#ifndef COUNTRIESMANAGER_H
#define COUNTRIESMANAGER_H

#include <vector>
using std::vector;

#include "Country.h"

class CountriesManager {

	public:
		static vector<Country>* findAll();
		static vector<int> findAllPrimaryKeys();
		static Country* findByPrimaryKey( unsigned int id );
};

#endif
