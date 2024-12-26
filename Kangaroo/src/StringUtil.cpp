#include "StringUtil.h"

#include <string.h>

char* StringUtil::trim(char *string) {
	const size_t len = sizeof(char) * (strlen(string) + 1);
	char *newString = static_cast<char *>(malloc(len));
	memset(newString, '\0', len);

	int newStringIndex = 0;

	for(unsigned int i = 0; i < strlen(string); i++)
		if(string[i] != '\r' && string[i] != '\n')
			newString[newStringIndex++] = string[i];
	
	return newString;
}

void StringUtil::tokenize(const string &str, vector<string> &tokens, const char *delim = " ") {
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delim, 0);
	// Find first "non-delimiter".
	string::size_type pos     = str.find_first_of(delim, lastPos);
	
	while (string::npos != pos || string::npos != lastPos) {
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delim, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delim, lastPos);
	}
}
