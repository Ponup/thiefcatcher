#include "HelpScreen.h"

#include <System.h>
#include <FontManager.h>
#include <Text.h>

#include "utilities/Translator.h"

#include "ui/Transitions.h"

HelpScreen::HelpScreen(Window * window_) : window(window_) {
	backgroundSurf.load("resources/images/menu/background.png");
	
	font.load("resources/fonts/FreeSansBold.ttf", 25);
	font.setColor(Color(63, 36, 18));
	
	fontValue.load("resources/fonts/FreeSans.ttf", 25);
	fontValue.setColor(Color(0, 0, 255));

	screenTitle = new Text(_("HELP"), &font);
	
	turnMusic0 = new Text(_("Turn on/off music"), &font);
	turnMusic1 = new Text(SDL_GetKeyName(SDLK_F2), &fontValue);
	
	turnSounds0 = new Text(_("Turn on/off sounds"), &font);
	turnSounds1 = new Text(SDL_GetKeyName(SDLK_F3), &fontValue);

	fullScreen0 = new Text(_("FullScreen"), &font);
	fullScreen1 = new Text(SDL_GetKeyName(SDLK_F4), &fontValue);

	saveGame0 = new Text(_("Save game"), &font);
	saveGame1 = new Text(SDL_GetKeyName(SDLK_F5), &fontValue);
	
	loadGame0 = new Text(_("Load game"), &font);
	loadGame1 = new Text(SDL_GetKeyName(SDLK_F6), &fontValue);

	quit0 = new Text(_("Quit"), &font);
	quit1 = new Text(SDL_GetKeyName(SDLK_ESCAPE), &fontValue);
}

void HelpScreen::show() {
	window->drawSurface(&backgroundSurf, Point(0, 0));
	
	int x = (window->getDimension().getWidth() >> 1) - (screenTitle->getDimension().getWidth() >> 1);
	screenTitle->draw(Point(x, 20), window);
	
	turnMusic0->draw(Point(200, 160), window);
	turnMusic1->draw(Point(480, 160), window);
	
	turnSounds0->draw(Point(200, 190), window);
	turnSounds1->draw(Point(480, 190), window);

	fullScreen0->draw(Point(200, 220), window);
	fullScreen1->draw(Point(480, 220), window);

	saveGame0->draw(Point(200, 250), window);
	saveGame1->draw(Point(480, 250), window);
	
	loadGame0->draw(Point(200, 280), window);
	loadGame1->draw(Point(480, 280), window);

	quit0->draw(Point(200, 310), window);
	quit1->draw(Point(480, 310), window);
	
	window->flip();

	System::waitUser();	
}

HelpScreen::~HelpScreen() {
	delete screenTitle;
	
	delete turnMusic0;
	delete turnMusic1;
	delete turnSounds0;
	delete turnSounds1;
	delete fullScreen0;
	delete fullScreen1;
	delete saveGame0;
	delete saveGame1;
	delete loadGame0;
	delete loadGame1;
	delete quit0;
	delete quit1;
}
