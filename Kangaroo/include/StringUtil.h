#pragma once

#include <string>
using std::string;

#include <vector>
using std::vector;

class StringUtil {

public:
	static char *trim(char *string);
	static void tokenize(const string& str, vector<string>& tokens, const char* delim);
};

