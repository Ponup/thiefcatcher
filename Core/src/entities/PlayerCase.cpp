#include "PlayerCase.h"

#include <algorithm>
using std::shuffle;
#include <random>

#include <sstream>
using std::endl;
using std::ostringstream;

#include <Random.h>

#include "entities/CountriesManager.h"
#include "entities/PlacesManager.h"
#include "entities/ClueFactory.h"

#include "utilities/Translator.h"

PlayerCase::PlayerCase() : currentPosition{0}, captureOrderExecuted{false}, lastMinuteCaptureOrderUsed{false}
{
}

PlayerCase::PlayerCase(const PlayerCase &playerCase)
{
    startDate = playerCase.startDate;
    currentDate = playerCase.currentDate;
    endDate = playerCase.endDate;
    criminal = playerCase.getCriminal();
    currentPosition = playerCase.getCurrentPosition();
    itinerary = playerCase.getItinerary();
    captureOrderExecuted = playerCase.isCaptureOrderExecuted();
    lastMinuteCaptureOrderUsed = playerCase.lastMinuteCaptureOrderUsed;
    stolenObject = playerCase.getStolenObject();
}

PlayerCase PlayerCase::operator=(const PlayerCase &playerCase)
{
    startDate = playerCase.startDate;
    currentDate = playerCase.currentDate;
    endDate = playerCase.endDate;
    criminal = playerCase.getCriminal();
    currentPosition = playerCase.getCurrentPosition();
    itinerary = playerCase.getItinerary();
    captureOrderExecuted = playerCase.isCaptureOrderExecuted();
    lastMinuteCaptureOrderUsed = playerCase.lastMinuteCaptureOrderUsed;
    stolenObject = playerCase.getStolenObject();
    return *this;
}

PlayerCase::~PlayerCase()
{
    delete startDate;
    delete currentDate;
    delete endDate;

    delete clues[2];
    delete clues[1];
    delete clues[0];
}

void PlayerCase::setCriminal(const Criminal &criminal)
{
    this->criminal = criminal;
}

Criminal PlayerCase::getCriminal() const
{
    return criminal;
}

void PlayerCase::setPlayer(const Player &player)
{
    this->player = player;
}

Player &PlayerCase::getPlayer()
{
    return player;
}

void PlayerCase::setCurrentPosition(int currentPosition)
{
    this->currentPosition = currentPosition;
}

int PlayerCase::getCurrentPosition() const
{
    return currentPosition;
}

void PlayerCase::setStolenObject(const string &stolenObject)
{
    this->stolenObject = stolenObject;
}

string PlayerCase::getStolenObject() const
{
    return stolenObject;
}

bool PlayerCase::isCaptureOrderExecuted() const
{
    return captureOrderExecuted;
}

void PlayerCase::setCaptureOrderExecuted(bool captureOrderExecuted)
{
    this->captureOrderExecuted = captureOrderExecuted;
}

void PlayerCase::setItinerary(vector<Country> itinerary)
{
    this->itinerary = itinerary;
}

vector<Country> PlayerCase::getItinerary() const
{
    return itinerary;
}

bool PlayerCase::rightCountry()
{
    return (currentCountry.getID() == previousCountry().getID());
}

Country &PlayerCase::previousCountry()
{
    return itinerary.at(currentPosition);
}

Country &PlayerCase::getCurrentCountry()
{
    return currentCountry;
}

Country &PlayerCase::nextCountry()
{
    return itinerary.at(currentPosition + 1);
}

Country &PlayerCase::getLastCountry()
{
    return itinerary[currentPosition];
}

void PlayerCase::setCurrentCountry(const Country &country)
{
    this->currentCountry = country;
}

void PlayerCase::updateCountries()
{
    if (currentPosition + 1 == itinerary.size())
    {
        return;
    }

    nextCountries[0] = (rightCountry() ? nextCountry() : previousCountry());

    vector<Country> randomCountries = CountriesManager::findRandom(3);
    for (int i = 0, pos = 1; i < 3 && pos < 3; i++)
    {
        if (randomCountries[i].getID() == nextCountries[0].getID())
        {
            continue;
        }

        nextCountries[pos] = randomCountries[i];
        pos++;
    }

    std::mt19937 rng(std::time(nullptr));
    shuffle(nextCountries, nextCountries + 3, rng);
}

void PlayerCase::updateCountryPlaces()
{
    countryPlaces = PlacesManager::findRandom(3);
}

void PlayerCase::updateClues()
{
    if (currentPosition + 1 == itinerary.size())
    {
        ClueFactory clueFactory;
        Clue *clue = clueFactory.createSameCountryClue();

        clues[0] = clues[1] = clues[2] = clue;
    }
    else
    {
        Criminal criminal = getCriminal();
        Country next = nextCountry();
        ClueFactory clueFactory;
        clues = clueFactory.createNRandomClues(*this, 3);
    }
}

bool PlayerCase::hasUsedLastMinuteCaptureOrder() const
{
    return lastMinuteCaptureOrderUsed;
}

void PlayerCase::useLastMinuteCaptureOrder()
{
    lastMinuteCaptureOrderUsed = true;
}
