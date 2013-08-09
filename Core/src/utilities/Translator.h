#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <Properties.h>

class Translator {
	private:
		static Properties props;

	public:
		static void init(const char *locale);
		static const char *translate(const char *key);
};

#define _(x) Translator::translate(x)

#endif

