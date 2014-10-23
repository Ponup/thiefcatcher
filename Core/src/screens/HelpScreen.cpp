#include "HelpScreen.h"

#include <Font.h>
#include <Text.h>

#include "utilities/Translator.h"

HelpScreen::HelpScreen(Window * window_) : window(window_) {
}

void HelpScreen::show() {
	Surface backgroundSurf("resources/images/menu/background.png");

	Font headerFont("resources/fonts/gtw.ttf", 45);
	headerFont.setColor(Color(255, 220, 220));
	Text headerText(_("Thief Catcher"), &headerFont);
	headerText.draw(Point(30, 10), &backgroundSurf);

	headerFont.setColor(Color(63, 36, 18));
	Text sectionText(_("Help"), &headerFont);
	int x = window->getDimension().w - sectionText.getDimension().w - 30;
	sectionText.draw(Point(x, 10), &backgroundSurf);

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
	
	turnMusic0.draw(Point(200, 160), &backgroundSurf);
	turnMusic1.draw(Point(480, 160), &backgroundSurf);
	
	turnSounds0.draw(Point(200, 190), &backgroundSurf);
	turnSounds1.draw(Point(480, 190), &backgroundSurf);

	fullScreen0.draw(Point(200, 220), &backgroundSurf);
	fullScreen1.draw(Point(480, 220), &backgroundSurf);

	saveGame0.draw(Point(200, 250), &backgroundSurf);
	saveGame1.draw(Point(480, 250), &backgroundSurf);
	
	loadGame0.draw(Point(200, 280), &backgroundSurf);
	loadGame1.draw(Point(480, 280), &backgroundSurf);

	quit0.draw(Point(200, 310), &backgroundSurf);
	quit1.draw(Point(480, 310), &backgroundSurf);

	window->drawSurface( &backgroundSurf );
	window->flip();

	SDL_Event event;
	bool quit = false;
	while(!quit) {
		while(SDL_PollEvent(&event)) {
			quit = (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN || event.type == SDL_QUIT);
		}
		SDL_Delay(10);		
	}
}

HelpScreen::~HelpScreen() {
}

