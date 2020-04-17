#include "CriminalFormatter.h"

#include <ctype.h>
#include <string.h>

#include "utilities/Translator.h"

string CriminalFormatter::formatGenre(const Criminal &criminal) {
	return formatGenre(criminal.getGenre());
}

string CriminalFormatter::formatGenre(const Genre& genre) {
	return (Genre::Female == genre ? _("female") : _("male"));
}

string CriminalFormatter::formatGenreArticle(const Criminal & criminal) {
	return (Genre::Female == criminal.getGenre() ? _("she") : _("he"));
}

string CriminalFormatter::formatGenrePossessive(const Criminal & criminal) {
	return (Genre::Female == criminal.getGenre() ? _("her") : _("his"));
}

