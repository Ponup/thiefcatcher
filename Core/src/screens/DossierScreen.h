#pragma once

#include <vector>
using std::vector;

#include <EventHandler.h>
#include <Window.h>
#include <SensitiveAreas.h>
#include <Font.h>
#include <Surface.h>

#include <Texture.h>
using Kangaroo::Texture;

#include "entities/Criminal.h"

#include <MouseCursor.h>
using Kangaroo::MouseCursor;

class DossierScreen : public EventHandler {

	Window *window;

	vector<Criminal> *criminals;

	unsigned char index;
	bool quit;

	SensitiveAreas sensAreas;

	Font fontName;
	Font font;

	Texture backgroundTexture;

	MouseCursor normalCursor, handCursor;

	void updateScreen(bool update);

public:
	DossierScreen(Window *window);
	virtual ~DossierScreen();

	void show();

	void onQuit(SDL_QuitEvent);
	void onMouseMotion(SDL_MouseMotionEvent);
	void onMouseButtonDown(SDL_MouseButtonEvent);
	void onMouseButtonUp(SDL_MouseButtonEvent);
	void onKeyDown(SDL_KeyboardEvent);
	void onKeyUp(SDL_KeyboardEvent);

};
