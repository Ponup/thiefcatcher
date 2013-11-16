#ifndef DOSSIERSCREEN_H_
#define DOSSIERSCREEN_H_

#include <vector>
using std::vector;

#include <EventHandler.h>
#include <Window.h>
#include <SensitiveAreas.h>
#include <Font.h>
#include <Surface.h>

#include "entities/Criminal.h"

class DossierScreen : public EventHandler {

private:
	Window *window;

	vector<Criminal> *criminals;

	unsigned char index;
	bool quit;

	SensitiveAreas sensAreas;
	
	Font fontName;
	Font font;
	
	Surface *backgroundSurf;

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

#endif
