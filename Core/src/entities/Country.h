#ifndef COUNTRY_H
#define COUNTRY_H

#include <vector>
#include <string>

#include <Surface.h>
#include <Point.h>

using std::vector;
using std::string;

class Country {

	private:
		unsigned char id;
		char *isoCode;
		char *code;
		char *name;
		char *description;
		char *treasure;
		char *flagDesc;
		char *capital;
		Point coord;

		vector<string> languages;
		vector<string> currencies;
		
	public:
		Country();
		Country(const Country &country);
		Country &operator=(const Country &country);
		~Country();

		void setIsoCode( const char *isoCode );
		const char* getIsoCode() const;
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
		void setFlagDescription(const char *flagDesc);
		const char *getFlagDescription() const;
		void setCoord(const Point &point);
		Point getCoord() const;
		void setLanguages( const vector<string> &languages );
		const vector<string> getLanguages() const;
		void setCurrencies( const vector<string> &currencies );
		const vector<string> getCurrencies() const;
		void setCapital( const char *capital );
		const char* getCapital() const;

		Surface *getPhoto() const;
		Surface *getFlag() const;

		const char *toString() const;
};

#endif

