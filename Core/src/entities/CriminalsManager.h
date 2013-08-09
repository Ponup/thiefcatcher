#ifndef CRIMINALSMANAGER_H
#define CRIMINALSMANAGER_H 1

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <Database.h>
#include <ResultSet.h>
#include "Criminal.h"

class CriminalsManager {

	private:
		static void completeCriminal(ResultSet &rs, Criminal *criminal, int i);
				
	public:
		static vector<Criminal> findAll();
		static vector<int> findAllPrimaryKeys();
		
		static vector<string> & findAllHairs();
		static vector<string> & findAllHobbies();
		static vector<string> & findAllFeatures();
		
		static Criminal *findByPrimaryKey(int id);
		static Criminal *findByFeatures(const char *genre, const char *hobby, const char *hair);
};

#endif
