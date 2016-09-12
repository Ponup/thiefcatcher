#pragma once

#include <Window.h>
#include <EventHandler.h>
#include <FontManager.h>
#include <SensitiveAreas.h>

#include <Text.h>
#include <Renderer.h>
#include <Texture.h>

using Kangaroo::Renderer;
using Kangaroo::Texture;

#include "utilities/Translator.h"
#include "utilities/Configurator.h"

class OptionsScreen : public EventHandler {

	Renderer* renderer;
	bool quit;
	Configurator configurator;
	SensitiveAreas sensAreas;

	int languageIndex;

	Font *fontValue;
	
	Texture backgroundTexture;
	
	Text *musicValue;
	Text *soundsValue;
	Text *languageValue;
	Text *fullscreenValue;

public:
	OptionsScreen(Renderer* renderer);
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
