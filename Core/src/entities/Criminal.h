#ifndef CRIMINAL_H
#define CRIMINAL_H

enum class Genre {
	Female = 0,
	Male
};

class Criminal {

	private:
		int id;
		char *name;
		Genre genre;
		char *hobby;
		char *hair;
		char *feature;
		
	public:
		Criminal();
		~Criminal();
		
		void setID(int id);
		int getID() const;
		
		void setName(const char *name);
		const char *getName() const;
		
		void setGenre( Genre genre );
		Genre getGenre() const;
		
		void setHobby(const char *hobby);
		const char *getHobby() const;
		
		void setHair(const char *hair);
		const char *getHair() const;
		
		void setFeature(const char *feature);
		const char *getFeature() const;

		const char *toString() const;
};

#endif
