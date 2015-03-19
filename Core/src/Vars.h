#pragma once

#include <vector>
using std::vector;

class Vars {
private:
	static vector<int> criminalsPK;		
		
public:	
	static void init();
	static vector<int> &listCriminalsPK();
};

