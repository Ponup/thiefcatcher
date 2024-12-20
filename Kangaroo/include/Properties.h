#pragma once

#include <utility>
using std::pair;

#include <map>
using std::map;

#include <string>
using std::string;

class Properties {

private:
	typedef pair<string, string> KeyValue;
	typedef map<string, string> StringsMap;
	
	StringsMap properties;

	string fileName;

public:
	Properties();
	virtual ~Properties();
				
	void load( const string& fileName);
	void save( const string* fileName = nullptr );
	
	string getProperty( const string& propertyName ) const;
	void setProperty( const string& propertyName, const string& propertyValue );
	
	bool getBoolProperty( const string& propertyName ) const;
	void setBoolProperty( const string& propertyName, bool propertyValue );
};

