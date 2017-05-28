#include "ClueManager.h"

#include <Random.h>

#include "utilities/Translator.h"

#include "entities/format/CriminalFormatter.h"

#include <string>
using std::string;

#include <cppformat/format.h>

ClueManager::ClueManager() {
    negativeAnswers = {
        _("Hello there, I'm afraid I haven't seen anything suspicious."),
        _("Sorry I don't know what you are talking about."),
        _("I didn't hear about thieves in this area.")
    };
}

ClueManager::~ClueManager() {
}

Clue *ClueManager::create(const Criminal &criminal, const Country &country) {
    Clue *clue = new Clue();

    string message;

    int kind = Random::nextInt(1, 7);
    switch (kind) {
        case 1:
            message = fmt::format(_("I heard {0} left in a rowboat, flying a {1} flag."), CriminalFormatter::formatGenreArticle(criminal, false), country.getFlagDescription());
            break;
        case 2:
            message = fmt::format(_("My sources told me {0} changed {1} money to {2}."),
                    CriminalFormatter::formatGenreArticle(criminal, false),
                    CriminalFormatter::formatGenrePossessive(criminal),
                    country.getFirstCurrency());
            break;
        case 3:
            message = fmt::format(_("{0} had {1} hair"),
                    CriminalFormatter::formatGenreArticle(criminal, true),
                    criminal.getHairColor());
            break;
        case 4:
            message = fmt::format(_("{0} mentioned that {1} {2}"),
                    CriminalFormatter::formatGenreArticle(criminal, true),
                    CriminalFormatter::formatGenreArticle(criminal, false),
                    criminal.getBuild());
            break;
        case 5:
            message = fmt::format(_("{0} had a {1}"),
                    CriminalFormatter::formatGenreArticle(criminal, true),
                    criminal.getFeature());
            break;
        case 6:
            message = fmt::format(_("All I know is that {0} was planning to trek across {1}."),
                    CriminalFormatter::formatGenreArticle(criminal, true),
                    country.getFlagDescription());
            break;
        case 7:
            int randomAnswerIndex = Random::nextInt(0, negativeAnswers.size() - 1);
            message = negativeAnswers.at(randomAnswerIndex);
            break;
    }

    clue->setMessage(message);

    return clue;
}

