#ifndef CLUE_H
#define CLUE_H

#include <string>
using std::string;

class Clue {

private:
	string message;

public:
	Clue();
	Clue(string message);
	~Clue();

	void setMessage(string message);
	string getMessage() const;
};

#endif

