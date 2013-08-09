#ifndef CLUE_H
#define CLUE_H

class Clue {

private:
	char *message;

public:
	Clue();
	Clue(const char *message);
	~Clue();

	void setMessage(const char *message);
	const char *getMessage() const;
};

#endif

