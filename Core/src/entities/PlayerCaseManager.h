#pragma once

#include "entities/PlayerCase.h"
#include "entities/Player.h"

class PlayerCaseManager {

    vector<int> criminalIds;

public:
    PlayerCaseManager();

    ~PlayerCaseManager();

    PlayerCase *createRandomCase(const Player &player);

    void save(const PlayerCase &playerCase);

    PlayerCase &load(int idPlayer);
};
