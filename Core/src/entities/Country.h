#ifndef COUNTRY_H
#define COUNTRY_H

#include <Surface.h>
#include <Point.h>

class Country {

	private:
		unsigned char id;
		char *code;
		char *name;
		char *description;
		char *treasure;
		char *coin;
		char *flagDesc;
		char *capital;
		char *language;
		Point coord;
		
	public:
		Country();
		Country(const Country &country);
		Country &operator=(const Country &country);
		~Country();

		void setCode( const char *code );
		const char* getCode() const;
		void setID(unsigned char id);
		unsigned char getID() const;
		void setName(const char *name);
		const char *getName() const;
		void setDescription(const char *description);
		const char *getDescription() const;
		void setTreasure(const char *treasure);
		const char *getTreasure() const;
		void setCoin(const char *coin);
		const char *getCoin() const;
		void setFlagDescription(const char *flagDesc);
		const char *getFlagDescription() const;
		void setCoord(const Point &point);
		Point getCoord() const;
		void setLanguage( const char *language );
		const char* getLanguage() const;
		void setCapital( const char *capital );
		const char* getCapital() const;

		Surface *getPhoto() const;
		Surface *getFlag() const;

		const char *toString() const;
};

#endif

