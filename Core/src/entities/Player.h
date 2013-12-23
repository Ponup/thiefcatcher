#ifndef PLAYER_H
#define PLAYER_H

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
		void setName(string name);
		string getName() const;
		void setRank(string rank);
		string getRank() const;
		void setResolved(unsigned int resolved);
		unsigned int getResolved() const;

		const char *toString() const;
};

#endif

