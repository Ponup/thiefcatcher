#pragma once

#include <vector>
using std::vector;

#include "Country.h"

class CountriesManager {

public:
	static vector<Country> findAll();
	static Country findByPrimaryKey( unsigned int id );
	static vector<Country> findRandom( int limit );
};

