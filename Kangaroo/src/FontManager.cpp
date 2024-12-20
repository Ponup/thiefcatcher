#include "FontManager.h"

FontMap FontManager::fontMap = FontMap();

Font* FontManager::getFont(const string& name, unsigned int size) {
	string fontKey = name + "_" + std::to_string(size);

	FontMap::iterator it = fontMap.find(fontKey.c_str());
	if (it != fontMap.end()) {
		return (*it).second;
	}

	string fontPath = "resources/fonts/" + name + ".ttf";
	Font *font = new Font(fontPath.c_str(), size);

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

