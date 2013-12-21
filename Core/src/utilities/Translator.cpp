#include "Translator.h"

#include <boost/locale.hpp>
using namespace boost::locale;

void Translator::init ( const char *localeCode ) {
	generator gen;
	gen.add_messages_path( "./resources/languages" );
	gen.add_messages_domain( "messages" );

	std::locale::global( gen( localeCode ) );
	std::cout.imbue(std::locale());
}

string Translator::translate( const char *id )
{
	return boost::locale::gettext( id );
}

