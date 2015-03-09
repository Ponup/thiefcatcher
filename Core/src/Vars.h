#pragma once

#include <vector>
using std::vector;

class Vars {
	private:
		static vector<int> criminalsPK;		
		static vector<int> countriesPK;
			
	public:	
		static void init();
		static vector<int> &listCriminalsPK();
		static vector<int> &listCountriesPK();
};

