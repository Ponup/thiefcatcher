#ifndef CLUEMANAGER_H_
#define CLUEMANAGER_H_

#include "entities/Clue.h"
#include "entities/Criminal.h"
#include "entities/Country.h"

class ClueManager {

public:
	ClueManager();
	~ClueManager();

	static Clue *create(const Criminal &criminal, const Country &country);
};

#endif

