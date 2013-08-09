#ifndef PLAYER_H
#define PLAYER_H

class Player {
	private:
		int id;
		const char *name;
		unsigned int resolved;
		
	public:
		Player();
		Player(const Player &player);
		Player operator=(const Player &player);
		~Player();
		
		void setID(int id);
		int getID() const;
		void setName(const char *name);
		const char *getName() const;
		void setResolved(unsigned int resolved);
		unsigned int getResolved() const;

		const char *toString() const;
};

#endif

