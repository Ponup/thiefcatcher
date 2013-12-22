#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "tinygettext/tinygettext.hpp"

#include <string>
using std::string;

class Translator {
	private:
		static tinygettext::Dictionary dict;
	public:
		static void init( const char *locale );
		static string translate( const char *id );
};

#define _(x) Translator::translate(x) 

#endif

