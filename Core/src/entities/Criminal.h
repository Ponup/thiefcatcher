#pragma once

#include <string>
using std::string;

enum class Genre {
	Female = 0,
	Male
};

class Criminal {

private:
	int id;
	string name;
	Genre genre;
	string hobby;
	string hair;
	string feature;
	
public:
	Criminal();
	~Criminal();
	
	void setID( int id );
	int getID() const;
	
	void setName( const string &name );
	string getName() const;
	
	void setGenre( Genre genre );
	Genre getGenre() const;
	
	void setHobby( const string &hobby );
	string getHobby() const;
	
	void setHair( const string &hair );
	string getHair() const;
	
	void setFeature( const string &feature );
	string getFeature() const;

	string toString() const;
};

