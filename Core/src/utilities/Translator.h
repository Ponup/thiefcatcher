#pragma once

#include <string>
using std::string;

class Translator {
public:
	static void init( const string &locale );
	static string translate( const char *id );
};

#define _(x) Translator::translate(x) 

