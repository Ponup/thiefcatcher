#pragma once 

#include <vector>
using std::vector;

#include <Surface.h>
#include <Window.h>
#include <Font.h>
#include <FontManager.h>
#include <Area.h>
#include <MediaSound.h>
#include <SensitiveAreas.h>
#include <EventHandler.h>

#include "MenuItem.h"

#include <Texture.h>
using Kangaroo::Texture;

#include <MouseCursor.h>
using Kangaroo::MouseCursor;

class Menu : public EventHandler {

	short selectedItem;

	vector<MenuItem> items;

	SensitiveAreas sensAreas;
	short currentItem;

	Font headerFont;
	Font font;

	Window *window;
	Texture backgroundTexture;
	Texture smokingPipeTexture;

	MediaSound sound;

	int lastY;

	MouseCursor normalCursor, handCursor;

	void update();

public:
	Menu(Window *window);
	virtual ~Menu();

	void setSelectedItem(short selectedItem);
	short addItem(string item);
	short getSelectedItem();

	void reset();

private:
	void onQuit(SDL_QuitEvent e);
	void onKeyDown(SDL_KeyboardEvent e);
	void onKeyUp(SDL_KeyboardEvent e);
	void onMouseButtonDown(SDL_MouseButtonEvent e);
	void onMouseButtonUp(SDL_MouseButtonEvent e);
	void onMouseMotion(SDL_MouseMotionEvent e);
};
