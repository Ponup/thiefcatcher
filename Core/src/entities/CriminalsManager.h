#pragma once

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <Database.h>
#include <ResultSet.h>
#include "Criminal.h"

#if defined(_WIN32) || defined(_WIN64)
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#endif

class CriminalsManager {

public:
	static vector<Criminal>* findAll();
	static vector<int> findAllPrimaryKeys();
	
	static vector<string> &findAllHairs();
	static vector<string> &findAllHobbies();
	static vector<string> &findAllFeatures();
	
	static Criminal* findByPrimaryKey( unsigned int id );
	static Criminal* findByFeatures( Genre genre, const string &hobby, const string &hair );
};

