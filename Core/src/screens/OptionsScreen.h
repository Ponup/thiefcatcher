#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include <Window.h>
#include <EventHandler.h>
#include <FontManager.h>
#include <SensitiveAreas.h>

#include <Text.h>

#include "utilities/Translator.h"
#include "utilities/Configurator.h"

#include "ui/Transitions.h"

class OptionsScreen : public EventHandler {

private:
	Window *window;
	bool quit;
	Configurator configurator;
	SensitiveAreas sensAreas;

	int languageIndex;

	Font *font;
	Font *fontValue;
	
	Surface *backgroundSurf;
	
	Text *screenTitle;
	
	Text *musicLabel, *musicValue;
	Text *soundsLabel, *soundsValue;
	Text *languageLabel, *languageValue;
	Text *fullscreenLabel, *fullscreenValue;

public:
	OptionsScreen(Window *window);
	virtual ~OptionsScreen();

	void show();

private:
	void updateScreen(bool update);
	void updateValues();

	void onQuit(SDL_QuitEvent);
	void onMouseMotion(SDL_MouseMotionEvent);
	void onMouseButtonDown(SDL_MouseButtonEvent);
	void onMouseButtonUp(SDL_MouseButtonEvent);
	void onKeyDown(SDL_KeyboardEvent);
	void onKeyUp(SDL_KeyboardEvent);
};

#endif
