#include "Translator.h"

#include <fstream>

#include "tinygettext/po_parser.hpp"

tinygettext::Dictionary Translator::dict;

void Translator::init ( const char *localeCode ) {
	std::string path = std::string("resources/languages/") + localeCode + "/LC_MESSAGES/messages.po";
	std::ifstream in( path );
	tinygettext::POParser::parse( path, in, dict );
	in.close();
}

string Translator::translate( const char *id )
{
	return dict.translate( id );
}

