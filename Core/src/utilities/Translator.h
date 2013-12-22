#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
using std::string;

class Translator {
	public:
		static void init( const char *locale );
		static string translate( const char *id );
};

#define _(x) Translator::translate(x) 

#endif

