#ifndef PROFILESCREEN_H_
#define PROFILESCREEN_H_

#include <EventHandler.h>
#include <Surface.h>
#include <Font.h>
#include <SensitiveAreas.h>

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "entities/PlayerCase.h"

class ProfileScreen : public EventHandler {

private:
	Surface *screen;
	PlayerCase *playerCase;

	Surface bgSurface;

	bool quit;

	int option;

	Font fontHeader;
	Font fontOptions;
	Font fontButtons;
	
	unsigned char genreIndex;

	unsigned char hairIndex;
	vector<string> hairsList;

	unsigned char hobbyIndex;
	vector<string> hobbiesList;

	unsigned char featureIndex;
	vector<string> featuresList;

	int returnCode;

	SensitiveAreas sensAreas;

	void drawElements();

public:
	ProfileScreen(Surface *screen_, PlayerCase *playerCase_);
	~ProfileScreen();

	int run();

	void onQuit(SDL_QuitEvent);
	void onMouseMotion(SDL_MouseMotionEvent);
	void onMouseButtonDown(SDL_MouseButtonEvent);
	void onMouseButtonUp(SDL_MouseButtonEvent);
	void onKeyDown(SDL_KeyboardEvent);
	void onKeyUp(SDL_KeyboardEvent);
};

#endif
