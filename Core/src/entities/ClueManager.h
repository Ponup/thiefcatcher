#pragma once

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "entities/Clue.h"
#include "entities/Criminal.h"
#include "entities/Country.h"

class ClueManager {

	vector<string> negativeAnswers;

public:
	ClueManager();
	~ClueManager();

	Clue *create(const Criminal &criminal, const Country &country);
};

