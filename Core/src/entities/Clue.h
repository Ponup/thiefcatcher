#pragma once

#include <string>
using std::string;

class Clue {

private:
	string message;

public:
	Clue();
	Clue(const string &message);
	~Clue();

	void setMessage( const string &message);
	string getMessage() const;
};


