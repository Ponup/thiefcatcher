#pragma once

#include <string>
using std::string;

class Player {
	private:
		int id;
		string name;
		string rank;
		unsigned int resolved;
		
	public:
		Player();
		Player(const Player &player);
		Player operator=(const Player &player);
		~Player();
		
		void setID(int id);
		int getID() const;
		void setName( const string& name);
		string getName() const;
		void setRank( const string& rank );
		string getRank() const;
		void setResolved(unsigned int resolved);
		unsigned int getResolved() const;
};

