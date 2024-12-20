#pragma once

#include <string>
using std::string;

namespace Kangaroo {

class HttpClient {

private:
	string url;

	static size_t writeCallback( char* buf, size_t size, size_t nmemb, void* cbdata );

public:
	HttpClient( const string &url );
	~HttpClient();

	void get( string *data );
	void post( const string &params );
};

}

