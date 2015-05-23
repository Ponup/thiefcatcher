#include "ClueManager.h"

#include <Random.h>

#include "utilities/Translator.h"

#include "entities/format/CriminalFormatter.h"

#include <string>
using std::string;

#include <cppformat/format.h>

ClueManager::ClueManager() {
}

ClueManager::~ClueManager() {
}

Clue *ClueManager::create(const Criminal &criminal, const Country &country) {
	Clue *clue = new Clue();
	string message;

	int kind = Random::nextInt( 1, 7 );
	switch (kind) {
	case 1:
		message = fmt::format(_("I heard {0} left in a rowboat, flying a {1} flag."), CriminalFormatter::formatGenreArticle(criminal, false), country.getFlagDescription() );
		break;
	case 2:
		sprintf(message, _("My sources tell me %s changed %s money to %s.").c_str(),
			CriminalFormatter::formatGenreArticle(criminal, false).c_str(),
			CriminalFormatter::formatGenrePossessive(criminal).c_str(),
			country.getCurrencies().at( 0 ).c_str() );
		break;
	case 3:
		sprintf(message, _("%s had %s hair").c_str(),
			CriminalFormatter::formatGenreArticle(criminal, true).c_str(),
			criminal.getHair().c_str());
		break;
	case 4:
		sprintf(message, _("%s mentioned that %s %s.").c_str(),
			CriminalFormatter::formatGenreArticle(criminal, true).c_str(),
			CriminalFormatter::formatGenreArticle(criminal, false).c_str(),
			criminal.getHobby().c_str());
		break;
	case 5:
		sprintf(message, _("%s had a %s").c_str(),
			CriminalFormatter::formatGenreArticle(criminal, true).c_str(),
			criminal.getFeature().c_str());
		break;
	case 6:
		sprintf(message, _("All I know is that %s was planning to trek across %s.").c_str(),
			CriminalFormatter::formatGenreArticle(criminal, true).c_str(),
			country.getFlagDescription().c_str());
		break;
	case 7:
		strcat(message, _("Sorry, I can't remember!").c_str());
		break;
	}
	
	clue->setMessage( message );

	return clue;
}

