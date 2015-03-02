#include "CriminalsManager.h"

#include <tinyxml2.h>

using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

vector<Criminal>* CriminalsManager::findAll() {
	static vector<Criminal> *criminals = NULL;

	if( NULL != criminals ) {
		return criminals;
	}

	criminals = new vector<Criminal>;

	XMLDocument doc;
	int errorCode = doc.LoadFile( "data/criminals.xml" );
	if( errorCode != tinyxml2::XML_NO_ERROR ) {
		// @todo Log the error.
		return criminals;
	}

	unsigned int criminalId = 0;
	XMLElement *rootNode = doc.RootElement();
	for( XMLElement *criminalNode = rootNode->FirstChildElement( "criminal" ); NULL != criminalNode; criminalNode = criminalNode->NextSiblingElement( "criminal" ) ) {
		Criminal criminal;
		criminal.setID( ++criminalId );
		criminal.setGenre( strncasecmp( "male", criminalNode->Attribute( "genre" ), 4 ) == 0 ? Genre::Male : Genre::Female );
		criminal.setName( criminalNode->FirstChildElement( "name" )->GetText() );
		criminal.setHobby( criminalNode->FirstChildElement( "trait" )->GetText() );
		criminal.setHair( criminalNode->FirstChildElement( "hair" )->GetText() );
		criminal.setFeature( criminalNode->FirstChildElement( "body" )->GetText() );
		criminals->push_back( criminal );
	}

	return criminals;	
}

vector<string> &CriminalsManager::findAllHairs() {
	vector<string> *list = new vector<string>;

	vector<Criminal> *criminals = findAll();
	for( vector<Criminal>::iterator it = criminals->begin(); it != criminals->end(); ++it ) {
		Criminal criminal = *it;
		list->push_back( criminal.getHair() );
	}

	return *list;		
}

vector<string> & CriminalsManager::findAllHobbies() {
	vector<string> *list = new vector<string>;

	vector<Criminal> *criminals = findAll();
	for( vector<Criminal>::iterator it = criminals->begin(); it != criminals->end(); ++it ) {
		Criminal criminal = *it;
		list->push_back( criminal.getHobby() );
	}

	return *list;			
}

vector<string> &CriminalsManager::findAllFeatures() {	
	vector<string> *list = new vector<string>;

	vector<Criminal> *criminals = findAll();
	for( vector<Criminal>::iterator it = criminals->begin(); it != criminals->end(); ++it ) {
		Criminal criminal = *it;
		list->push_back( criminal.getFeature() );
	}

	return *list;
}

Criminal *CriminalsManager::findByFeatures( Genre genre, const char *hobby, const char *hair) {
	vector<Criminal> *criminals = findAll();
	for( vector<Criminal>::iterator it = criminals->begin(); it != criminals->end(); ++it ) {
		Criminal criminal = *it;
		if( genre == criminal.getGenre() && strcasecmp( criminal.getHobby(), hobby ) == 0 && strcasecmp( criminal.getHair(), hair ) == 0 ) {
			return new Criminal( criminal );
		}
	}

	return NULL;
}

vector<int> CriminalsManager::findAllPrimaryKeys() {
	vector<int> primaryKeys;

	vector<Criminal> *criminals = findAll();
	for( vector<Criminal>::iterator it = criminals->begin(); it != criminals->end(); ++it ) {
		Criminal criminal = *it;
		primaryKeys.push_back( criminal.getID() );
	}

	return primaryKeys;	
}

Criminal *CriminalsManager::findByPrimaryKey( unsigned int id ) {
	vector<Criminal> *criminals = findAll();
	return ( id - 1 < criminals->size() ? new Criminal( criminals->at( id - 1 ) ) : NULL );
}

