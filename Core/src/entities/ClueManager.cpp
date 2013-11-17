#include "ClueManager.h"

#include <Random.h>

#include "utilities/Translator.h"

#include "entities/format/CriminalFormatter.h"

ClueManager::ClueManager() {
}

ClueManager::~ClueManager() {
}

Clue *ClueManager::create(const Criminal &criminal, const Country &country) {
	char *message = (char *)malloc(sizeof(char) * 200);
	memset(message, '\0', 200);

	int kind = Random::nextInt(1, 7);
	switch (kind) {
	case 1:
		sprintf(message, _("I heard %s left in a rowboat, flying a %s flag."),
			CriminalFormatter::formatGenreArticle(criminal, false),
			country.getFlagDescription());
		break;
	case 2:
		sprintf(message, _("My sources tell me %s changed %s money to %s."),
			CriminalFormatter::formatGenreArticle(criminal, false),
			CriminalFormatter::formatGenrePossessive(criminal),
			country.getCurrencies().at( 0 ).c_str() );
		break;
	case 3:
		sprintf(message, _("%s had %s hair"),
			CriminalFormatter::formatGenreArticle(criminal, true),
			criminal.getHair());
		break;
	case 4:
		sprintf(message, _("%s mentioned that %s %s."),
			CriminalFormatter::formatGenreArticle(criminal, true),
			CriminalFormatter::formatGenreArticle(criminal, false),
			criminal.getHobby());
		break;
	case 5:
		sprintf(message, _("%s had a %s"),
			CriminalFormatter::formatGenreArticle(criminal, true),
			criminal.getFeature());
		break;
	case 6:
		sprintf(message, _("All I know is that %s was planning to trek across %s."),
			CriminalFormatter::formatGenreArticle(criminal, true),
			country.getFlagDescription());
		break;
	case 7:
		sprintf(message, "Sorry, I can't remember!");
		break;
	}

	return new Clue(message);
}

