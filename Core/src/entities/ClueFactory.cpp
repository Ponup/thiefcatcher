#include "entities/ClueFactory.h"

#include <fmt/format.h>

#include "entities/format/GenreFormatter.h"

#include <Random.h>

#include "utilities/Translator.h"

#include <algorithm>
using std::random_shuffle;

ClueFactory::ClueFactory() {
    negativeAnswers = {
        _("Hello there, I'm afraid I haven't seen anything suspicious."),
        _("Sorry I don't know what you are talking about."),
        _("I didn't hear about thieves in this area."),
        _("Not now, sorry. I'm busy."),
        _("I am too old to remember."),
        _("I would love to help out but I just arrived to this place."),
        _("I'd rather not say."),
    };
}

Clue** ClueFactory::createNRandomClues(PlayerCase& playerCase, size_t numClues) const {
    vector<ClueType> clueTypes{ClueType::Country, ClueType::Country, ClueType::Criminal, ClueType::Criminal, ClueType::Negative};
    random_shuffle(clueTypes.begin(), clueTypes.end());
    
    Clue** clues = new Clue*[numClues];
    for(size_t i = 0; i < numClues; i++) {
        if(clueTypes[i] == ClueType::Country) {
            clues[i] = createNextCountryClue(playerCase);
        }
        else if(clueTypes[i] == ClueType::Criminal) {
            clues[i] = createCriminalClue(playerCase);
        }
        else {
            clues[i] = createNegativeClue();
        }
    }
    
    return clues;
}

Clue* ClueFactory::createWrongCountryClue() const {
    return new Clue(_("Sorry, but the criminal was reported to be seen in another country."));
}

Clue* ClueFactory::createSameCountryClue() const {
    return new Clue(_("I have seen the criminal around in this country, hurry up!"));
}

Clue* ClueFactory::createCriminalClue(PlayerCase& playerCase) const {
    string message;

    int kind = Random::nextInt(0, 2);
    switch (kind) {
        case 0:
            message = fmt::format(_("I think {0} had {1} hair."),
                    GenreFormatter::formatSubjectPronoun(playerCase.criminal.getGenre()),
                    playerCase.criminal.getHair());
            break;
        case 1:
            message = fmt::format(_("If I am not mistaken, {0} had {1} build."),
                    GenreFormatter::formatSubjectPronoun(playerCase.criminal.getGenre()),
                    playerCase.criminal.getBuild());
            break;
        case 2:
            message = fmt::format(_("There was something peculiar about the thief... oh yes, {0} {1}."),
                    GenreFormatter::formatPossessiveAdjective(playerCase.criminal.getGenre()),
                    playerCase.criminal.getFeature());
            break;
    }

    return new Clue{message};
}

Clue* ClueFactory::createNextCountryClue(PlayerCase& playerCase) const {
    string message;

    int kind = Random::nextInt(0, 3);
    switch (kind) {
        case 0:
            message = fmt::format(_("I think {0} had a map with a country flag with {1}"), GenreFormatter::formatSubjectPronoun(playerCase.criminal.getGenre()), playerCase.nextCountry().getFlag());
            break;
        case 1:
            message = fmt::format(_("My sources told me {0} changed {1} money to {2}."),
                    GenreFormatter::formatSubjectPronoun(playerCase.criminal.getGenre()),
                    GenreFormatter::formatPossessiveAdjective(playerCase.criminal.getGenre()),
                    playerCase.nextCountry().getFirstCurrency());
            break;
        case 2:
            message = fmt::format(_("The next country {0} was planning to visit is {1}."),
                    GenreFormatter::formatSubjectPronoun(playerCase.criminal.getGenre()),
                    playerCase.nextCountry().getName());
            break;
        case 3:
            message = fmt::format(_("Sources told me the thief was planning to travel to {0} next. I can't remember which country is that city though. Can you?"),
                    playerCase.nextCountry().getCapital());
            break;
    }

    return new Clue{message};
}

Clue* ClueFactory::createNegativeClue() const {
    int randomAnswerIndex = Random::nextInt(0, negativeAnswers.size() - 1);
    string message = negativeAnswers.at(randomAnswerIndex);
    return new Clue{message};
}

Clue* ClueFactory::createLastMinuteCaptureOrderClue() const {
    return new Clue{"Issue a capture order right now or the thief will get away!"};
}