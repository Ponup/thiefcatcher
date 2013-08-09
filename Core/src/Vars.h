#ifndef VAR_H
#define VAR_H

#include <vector>
using std::vector;

class Vars {
	private:
		static vector<int> criminalsPK;		
		static vector<int> countriesPK;
		static vector<int> placesPK;
			
	public:	
		static void init();
		static vector<int> &listCriminalsPK();
		static vector<int> &listCountriesPK();
		static vector<int> &listPlacesPK();
};

#endif
