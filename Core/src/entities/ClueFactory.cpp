#include "entities/ClueFactory.h"

#include <fmt/format.h>

#include "entities/format/CriminalFormatter.h"

#include <Random.h>

#include "utilities/Translator.h"

ClueFactory::ClueFactory() {
    negativeAnswers = {
        _("Hello there, I'm afraid I haven't seen anything suspicious."),
        _("Sorry I don't know what you are talking about."),
        _("I didn't hear about thieves in this area."),
        _("Not now, sorry. I'm busy."),
        _("I am too old to remember."),
        _("I would love to help out but I just arrived to this place."),
    };
}

Clue** ClueFactory::createNRandomClues(PlayerCase& playerCase, size_t numClues) const {
    Clue** clues = new Clue*[3];
    clues[0] = createCriminalClue(playerCase);
    clues[1] = createNextCountryClue(playerCase);
    clues[2] = createNegativeClue();
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

    int kind = Random::nextInt(0, 3);
    switch (kind) {
        case 0:
            message = fmt::format(_("{0} had {1} hair."),
                    CriminalFormatter::formatGenreArticle(playerCase.criminal, true),
                    playerCase.criminal.getHair());
            break;
        case 1:
            message = fmt::format(_("{0} had {1} build."),
                    CriminalFormatter::formatGenreArticle(playerCase.criminal, true),
                    playerCase.criminal.getBuild());
            break;
        case 2:
            message = fmt::format(_("There was something peculiar about the thief... oh yes, {0} {1}."),
                    CriminalFormatter::formatGenrePossessive(playerCase.criminal),
                    playerCase.criminal.getFeature());
            break;
        case 3:
            int randomAnswerIndex = Random::nextInt(0, negativeAnswers.size() - 1);
            message = negativeAnswers.at(randomAnswerIndex);
            break;
    }

    return new Clue{message};
}

Clue* ClueFactory::createNextCountryClue(PlayerCase& playerCase) const {
    string message;

    int kind = Random::nextInt(0, 3);
    switch (kind) {
        case 0:
            message = fmt::format(_("I think {0} had a map with a country flag with {1}"), CriminalFormatter::formatGenreArticle(playerCase.criminal, false), playerCase.nextCountry().getFlag());
            break;
        case 1:
            message = fmt::format(_("My sources told me {0} changed {1} money to {2}."),
                    CriminalFormatter::formatGenreArticle(playerCase.criminal, false),
                    CriminalFormatter::formatGenrePossessive(playerCase.criminal),
                    playerCase.nextCountry().getFirstCurrency());
            break;
        case 2:
            message = fmt::format(_("The next country {0} was planning to visit is {1}."),
                    CriminalFormatter::formatGenreArticle(playerCase.criminal, true),
                    playerCase.nextCountry().getName());
            break;
        case 3:
            int randomAnswerIndex = Random::nextInt(0, negativeAnswers.size() - 1);
            message = negativeAnswers.at(randomAnswerIndex);
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