#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <libintl.h>

class Translator {
	public:
		static void init(const char *locale);
};

#define _(x) gettext(x) 

#endif

