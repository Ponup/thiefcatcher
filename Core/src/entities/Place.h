#pragma once

#include <string>
using std::string;

#include <Surface.h>

class Place {
	private:
		unsigned char id;
		string name;
		
	public:
		Place();
		~Place();

		void setId(unsigned char id);
		unsigned char getId() const;
		void setName( const string &name );
		string getName() const;
		
		Surface* getSurface() const;
		Surface* getCharacterSurface() const;
};
