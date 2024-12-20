#include "HttpClient.h"

#include <curl/curl.h>

namespace Kangaroo {

HttpClient::HttpClient( const string &url ) : url( url ) {
}

HttpClient::~HttpClient() {}

size_t HttpClient::writeCallback( char* buf, size_t size, size_t nmemb, void* cbdata ) {
	string *data = (string *)cbdata;
	for ( unsigned int c = 0; c < size * nmemb; c++ ) {
		data->push_back( buf[ c ] );
	}
	return size * nmemb;
}

void HttpClient::get( string *data ) {
	CURL *curl;

	curl_global_init( CURL_GLOBAL_ALL );
	curl = curl_easy_init();

	curl_easy_setopt( curl, CURLOPT_URL, url.c_str() );
	curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, &HttpClient::writeCallback );
	curl_easy_setopt( curl, CURLOPT_WRITEDATA, data );
	curl_easy_setopt( curl, CURLOPT_TIMEOUT, 6 );
	curl_easy_setopt( curl, CURLOPT_VERBOSE, 0 );

	curl_easy_perform( curl );

	curl_easy_cleanup( curl );
	curl_global_cleanup();
}

void HttpClient::post( const string &params ) {
	CURL *curl;

	curl_global_init( CURL_GLOBAL_ALL );
	curl = curl_easy_init();

	curl_easy_setopt( curl, CURLOPT_URL, url.c_str() );
	curl_easy_setopt( curl, CURLOPT_POSTFIELDS, params.c_str() );
	curl_easy_setopt( curl, CURLOPT_TIMEOUT, 3 );
	curl_easy_setopt( curl, CURLOPT_VERBOSE, 0 );

	curl_easy_perform( curl );

	curl_easy_cleanup( curl );
	curl_global_cleanup();
}

}

