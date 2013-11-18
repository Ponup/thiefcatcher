#include "CriminalFormatter.h"

#include <ctype.h>
#include <string.h>

#include "utilities/Translator.h"

const char *CriminalFormatter::formatGenre( const Criminal &criminal ) {
	return formatGenre( criminal.getGenre() );
}

const char *CriminalFormatter::formatGenre( Genre genre ) {
	return ( Genre::Female == genre ? _("female") : _("male") );
}

/**
 * @todo Actually do something with the second parameter.
 */
const char *CriminalFormatter::formatGenreArticle( const Criminal & criminal, bool capitalizeFirst ) {
	return ( Genre::Female == criminal.getGenre() ? _("she") : _("he") );
}

const char *CriminalFormatter::formatGenrePossessive(const Criminal & criminal) {
	return ( Genre::Female == criminal.getGenre() ? _("her") : _("his") );
}

