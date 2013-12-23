#include "HelpScreen.h"

#include <Font.h>
#include <Text.h>
#include <System.h>

#include "utilities/Translator.h"

#include "ui/Transitions.h"

HelpScreen::HelpScreen(Window * window_) : window(window_) {
}

void HelpScreen::show() {
	Surface backgroundSurf("resources/images/menu/background.png");

	window->drawSurface(&backgroundSurf, Point(0, 0));

	Font headerFont("resources/fonts/gtw.ttf", 45);
	headerFont.setColor(Color(255, 220, 220));
	Text headerText(_("Thief Catcher"), &headerFont);
	headerText.draw(Point(30, 10), window);

	headerFont.setColor(Color(63, 36, 18));
	Text sectionText(_("Help"), &headerFont);
	int x = window->getDimension().getWidth() - sectionText.getDimension().getWidth() - 30;
	sectionText.draw(Point(x, 10), window);

	Font font("resources/fonts/FreeSansBold.ttf", 25);
	font.setColor(Color(63, 36, 18));
	
	Font fontValue("resources/fonts/FreeSans.ttf", 25);
	fontValue.setColor(Color(0, 0, 255));

	Text turnMusic0(_("Turn on/off music"), &font);
	Text turnMusic1(SDL_GetKeyName(SDLK_F2), &fontValue);
	
	Text turnSounds0(_("Turn on/off sounds"), &font);
	Text turnSounds1(SDL_GetKeyName(SDLK_F3), &fontValue);

	Text fullScreen0(_("FullScreen"), &font);
	Text fullScreen1(SDL_GetKeyName(SDLK_F4), &fontValue);

	Text saveGame0(_("Save game"), &font);
	Text saveGame1(SDL_GetKeyName(SDLK_F5), &fontValue);
	
	Text loadGame0(_("Load game"), &font);
	Text loadGame1(SDL_GetKeyName(SDLK_F6), &fontValue);

	Text quit0(_("Quit"), &font);
	Text quit1(SDL_GetKeyName(SDLK_ESCAPE), &fontValue);
	
	turnMusic0.draw(Point(200, 160), window);
	turnMusic1.draw(Point(480, 160), window);
	
	turnSounds0.draw(Point(200, 190), window);
	turnSounds1.draw(Point(480, 190), window);

	fullScreen0.draw(Point(200, 220), window);
	fullScreen1.draw(Point(480, 220), window);

	saveGame0.draw(Point(200, 250), window);
	saveGame1.draw(Point(480, 250), window);
	
	loadGame0.draw(Point(200, 280), window);
	loadGame1.draw(Point(480, 280), window);

	quit0.draw(Point(200, 310), window);
	quit1.draw(Point(480, 310), window);
	
	window->flip();

	System::waitUser();	
}

HelpScreen::~HelpScreen() {
}

