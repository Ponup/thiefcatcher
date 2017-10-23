#pragma once

#include <SDL.h>
#include <Surface.h>
#include <FontManager.h>
#include <Text.h>

#include <string>
using std::string;

class InputBox {

	string text;
	Color background;
	Color foreground;

	Font *font;
	Point point;
	Dimension dimension;

	unsigned short maxChars;

public:
	Text line;

	InputBox();
	InputBox(Font *font_, const Point &point_, const Dimension &dimension_);
	~InputBox();

	void setBackground(const Color &background);
	void setForeground(const Color &foreground);
	void setFont(Font *font);
	void handleEvent(SDL_Event &event);
	void update();

	void setMaxChars(unsigned short maxChars);
	unsigned short getMaxChars() const;

	string getText();
	string get();

	void clear();

	void putChar(SDL_Keycode key);
};
