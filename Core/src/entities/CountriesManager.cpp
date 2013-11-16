#include "CountriesManager.h"

#include <tinyxml2.h>

using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

vector<Country>* CountriesManager::findAll() {
	static vector<Country> *countries = NULL;

	if( NULL != countries ) {
		return countries;
	}

	countries = new vector<Country>;

	XMLDocument xmlDoc;
	int errorCode = xmlDoc.LoadFile( "data/countries.xml" );
	if( tinyxml2::XML_NO_ERROR != errorCode ) {
		return countries;
	}

	unsigned int id = 0;
	XMLElement *rootNode = xmlDoc.RootElement();
	for( XMLElement *countryNode = rootNode->FirstChildElement( "country" ); NULL != countryNode; countryNode = countryNode->NextSiblingElement( "country" ) ) {
		Country country;
		country.setID( ++id );
		country.setCode( countryNode->Attribute( "code" ) );
		country.setName( countryNode->FirstChildElement( "name" )->GetText() );
		country.setCapital( countryNode->FirstChildElement( "capital" )->GetText() );
		country.setLanguage( countryNode->FirstChildElement( "language" )->GetText() );
		country.setCoin( countryNode->FirstChildElement( "currency" )->GetText() );
		country.setTreasure( countryNode->FirstChildElement( "treasure" )->GetText() );
//		country.setName( countryNode->FirstChildElement( "coord-lat" )->GetText() );
		country.setCoord( Point( 1, 2 ) );
		country.setDescription( countryNode->FirstChildElement( "description" )->GetText() );
		country.setFlagDescription( countryNode->FirstChildElement( "flag-description" )->GetText() );
		printf("%s\n",country.toString());
		countries->push_back( country );
	}

	return countries;	
}

vector<int> CountriesManager::findAllPrimaryKeys() {
	vector<int> primaryKeys;

	vector<Country> *countries = findAll();
	for( vector<Country>::iterator it = countries->begin(); it != countries->end(); it++ ) {
		primaryKeys.push_back( (*it).getID() );
	}

	return primaryKeys;	
}

Country *CountriesManager::findByPrimaryKey( unsigned int id ) {
	vector<Country> *countries = findAll();
	return ( id - 1 < countries->size() ? new Country( countries->at( id - 1 ) ) : NULL );
}

