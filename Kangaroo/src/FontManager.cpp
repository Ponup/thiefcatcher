#include "FontManager.h"

FontMap FontManager::fontMap = FontMap();

Font* FontManager::getFont(const string& name, unsigned int size) {
	string fontKey = name + "_" + std::to_string(size);

	auto it = fontMap.find(fontKey);
	if (it != fontMap.end()) {
		return (*it).second;
	}

	const string fontPath = "resources/fonts/" + name + ".ttf";
	auto font = new Font(fontPath.c_str(), size);

	fontMap.insert(FontMap::value_type(fontKey, font));

	return font;
}

void FontManager::destroy() {
	FontMap::iterator it;
	for (it = fontMap.begin(); it != fontMap.end(); it++) {
		//delete (*it).second;
	}
	fontMap.clear();
}

