#include "CriminalFormatter.h"

#include "utilities/Translator.h"

CriminalFormatter::CriminalFormatter()
{
}

CriminalFormatter::~CriminalFormatter()
{
}

const char *CriminalFormatter::formatGenreArticle(const Criminal & criminal, bool start) {
	if(strncmp(criminal.getSex(), "Male", 4) == 0) {
		return start ? _("He") : _("he");
	} else {
		return start ? _("She") : _("she");
	}
}

const char *CriminalFormatter::formatGenrePossessive(const Criminal & criminal) {
	if(strncmp(criminal.getSex(), "Male", 4) == 0) {
		return false ? _("His") : _("his");
	} else {
		return false ? _("Her") : _("her");
	}	
}

