#pragma once

#include <map>
using std::map;

#include <string>
using std::string;

#include "Font.h"

typedef map<string, Font*> FontMap;

class FontManager {

	static FontMap fontMap;

public:
	static Font* getFont(const string& name, unsigned int size);
	static void destroy();
};

