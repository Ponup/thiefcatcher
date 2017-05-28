#pragma once

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "utilities/DateTime.h"

#include "entities/Criminal.h"
#include "entities/Player.h"
#include "entities/Country.h"
#include "entities/Clue.h"

class PlayerCase {
public:
    DateTime *startDate;
    DateTime *currentDate;
    DateTime *endDate;

    unsigned int currentPosition;
    Criminal criminal;
    Player player;

    Country currentCountry;
    Country nextCountries[3];

    Clue *clues[3];

    string stolenObject;
    bool captureOrderExecuted;

public:
    vector<Country> itinerary;

    PlayerCase();
    PlayerCase(const PlayerCase &playerCase);
    ~PlayerCase();

    PlayerCase operator=(const PlayerCase &playerCase);

    bool rightCountry();
    Country &nextCountry();
    Country &getCurrentCountry();
    Country &previousCountry();
    Country &getLastCountry();

    void setPlayer(const Player &player);
    Player& getPlayer();
    void setCriminal(const Criminal &criminal);
    Criminal getCriminal() const;
    void setCurrentPosition(int currentPosition);
    int getCurrentPosition() const;

    void setStolenObject(const string &stolenObject);
    string getStolenObject() const;

    bool isCaptureOrderExecuted() const;
    void setCaptureOrderExecuted(bool captureOrderExecuted);

    void setItinerary(vector<Country> itinerary);
    vector<Country> getItinerary() const;

    void setCurrentCountry(const Country &country);

    void updateCountries();
    void updateClues();

    const char *toString() const;
};

