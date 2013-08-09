#ifndef CRIMINALFORMATTER_H_
#define CRIMINALFORMATTER_H_

#include "entities/Criminal.h"

class CriminalFormatter {
public:
	CriminalFormatter();
	virtual ~CriminalFormatter();

	static const char *formatGenreArticle(const Criminal &criminal, bool start);
	static const char *formatGenrePossessive(const Criminal &criminal);
};

#endif

