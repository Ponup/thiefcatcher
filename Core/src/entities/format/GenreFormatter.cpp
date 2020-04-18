#include "entities/format/GenreFormatter.h"

#include <ctype.h>
#include <string.h>

#include "utilities/Translator.h"

#include <exception>
using std::exception;

string GenreFormatter::format(const Genre &genre)
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

string GenreFormatter::formatSubjectPronoun(const Genre &criminal)
{
	return Genre::Female == criminal ? _("she") : _("he");
}

string GenreFormatter::formatObjectPronoun(const Genre &criminal)
{
	return Genre::Female == criminal ? _("her") : _("him");
}

string GenreFormatter::formatPossessiveAdjective(const Genre &criminal)
{
	return Genre::Female == criminal ? _("her") : _("his");
}
