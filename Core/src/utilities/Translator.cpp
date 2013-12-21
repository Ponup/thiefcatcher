#include "Translator.h"

#include <locale.h>
#include <stdlib.h>

void Translator::init ( const char *locale ) {
	setlocale( LC_ALL, "" );
	setenv( "LANGUAGE", locale, 1 );
	bindtextdomain( "messages", "resources/languages" );
	bind_textdomain_codeset( "messages", "utf8" );
	textdomain( "messages" );
}

