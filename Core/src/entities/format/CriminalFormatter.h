#ifndef CRIMINALFORMATTER_H_
#define CRIMINALFORMATTER_H_

#include "entities/Criminal.h"

class CriminalFormatter {

	public:
		static const char *formatGenre( const Criminal &criminal );
		static const char *formatGenre( Genre genre );
		static const char *formatGenreArticle( const Criminal &criminal, bool capitalizeFirst );
		static const char *formatGenrePossessive( const Criminal &criminal );
};

#endif

