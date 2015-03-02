#ifndef PLACE_H
#define PLACE_H

#include <Surface.h>

class Place {
	private:
		unsigned char id;
		char *name;
		
	public:
		Place();
		Place(const Place &place);
		Place & operator=(const Place &place);
		~Place();

		void setId(unsigned char id);
		unsigned char getId() const;
		void setName(const char *name);
		const char *getName() const;
		
		Surface *getSurface() const;
		Surface *getCharacterSurface() const;
};

#endif
