#pragma once

#include "entities/Clue.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "entities/Clue.h"
#include "entities/Criminal.h"
#include "entities/Country.h"
#include "PlayerCase.h"

enum class ClueType {
    Negative,
    Country,
    Criminal
};

class ClueFactory {

    vector<string> negativeAnswers;

public:
    ClueFactory();

    Clue** createNRandomClues(PlayerCase& playerCase, size_t numClues) const;
    Clue* createWrongCountryClue() const;
    Clue* createNextCountryClue(PlayerCase& playerCase) const;
    Clue* createSameCountryClue() const;
    Clue* createCriminalClue(PlayerCase& playerCase) const;
    Clue* createNegativeClue() const;
};