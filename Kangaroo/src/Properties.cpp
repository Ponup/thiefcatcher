#include "Properties.h"

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <iostream>
using std::ios;

using std::endl;

#include <stdexcept>
using std::runtime_error;

Properties::Properties() {
}

Properties::~Properties() {
}

void Properties::load( const string& fileName ) {

	this->fileName = fileName;

	properties.clear();

	ifstream inputStream( fileName );
	string line;
	while( std::getline( inputStream, line ) )
	{
		if( line.size() == 0 || line[0] == '#' )
		{
			continue;
		}	

		size_t equalPos = line.find( '=' );
		if( string::npos == equalPos )
		{
			continue;
		}

		string key = line.substr( 0, equalPos );
		string value = line.substr( equalPos + 1 );

		properties.insert( KeyValue( key, value ) );
	}
	inputStream.close();
}

void Properties::save( const string* fileName ) {
	string outputFilename = this->fileName;
	if( nullptr != fileName )
	{
		outputFilename = *fileName;
	}

	ofstream outputStream( outputFilename, ios::out | ios::trunc );
	if( !outputStream.is_open() )
	{
		return;
	}

	StringsMap::const_iterator it;
	for(it = properties.begin(); it != properties.end(); it++) {
		string key = it->first;
		string value = it->second;

		outputStream << key << "=" << value << endl;
	}
	outputStream.close();
}

string Properties::getProperty( const string& propertyName ) const {
	auto it = properties.find(propertyName);
	if(it == properties.end()) {
		return "";
	}
	return it->second;
}

void Properties::setProperty( const string& propertyName, const string& propertyValue ) {
	StringsMap::const_iterator it;
	it = properties.find( propertyName );
	properties.erase( it->first );
	properties.insert( KeyValue( propertyName, propertyValue ) );
}

bool Properties::getBoolProperty( const string& propertyName ) const {
	string p = getProperty( propertyName );
	
	return ( "True" == p );
}

void Properties::setBoolProperty( const string& propertyName, bool propertyValue ) {
	setProperty( propertyName, ( propertyValue ? "True" : "False" ) );
}

