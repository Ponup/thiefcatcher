#include "CriminalFormatter.h"

#include <ctype.h>
#include <string.h>

#include "utilities/Translator.h"

#include <exception>
using std::exception;

string CriminalFormatter::formatGenre(const Criminal &criminal)
{
	return formatGenre(criminal.getGenre());
}

string CriminalFormatter::formatGenre(const Genre &genre)
{
	switch (genre)
	{
	case Genre::_Unset:
		return _("unset");
	case Genre::Female:
		return _("female");
	case Genre::Male:
		return _("male");
	case Genre::_Count:
		break;
	}

	return _("unknown");
}

string CriminalFormatter::formatGenreArticle(const Criminal &criminal)
{
	return Genre::Female == criminal.getGenre() ? _("she") : _("he");
}

string CriminalFormatter::formatGenrePossessive(const Criminal &criminal)
{
	return Genre::Female == criminal.getGenre() ? _("her") : _("his");
}
