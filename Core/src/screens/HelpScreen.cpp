#include "HelpScreen.h"

#include <Font.h>
#include <Text.h>

#include "Game.h"

#include "utilities/Translator.h"

HelpScreen::HelpScreen(Renderer* renderer) : renderer(renderer) {
}

void HelpScreen::show() {
	Texture backgroundTexture(renderer->internal, "resources/images/menu/background.png");

	renderer->drawTexture(&backgroundTexture);

	Font headerFont("resources/fonts/gtw.ttf", 45);
	headerFont.setColor(Color(255, 220, 220));
	Text headerText(_("Thief Catcher"), &headerFont);
	renderer->drawText(&headerText, Point(30, 10));

	headerFont.setColor(Color(63, 36, 18));
	Text sectionText(_("Help"), &headerFont);
	int x = Game::Width - sectionText.getDimension().w - 30;
	renderer->drawText(&sectionText, Point(x, 10));

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
	
	renderer->drawText(&turnMusic0, Point(200, 160));
	renderer->drawText(&turnMusic1, Point(480, 160));
	
	renderer->drawText(&turnSounds0, Point(200, 190));
	renderer->drawText(&turnSounds1, Point(480, 190));

	renderer->drawText(&fullScreen0, Point(200, 220));
	renderer->drawText(&fullScreen1, Point(480, 220));

	renderer->drawText(&saveGame0, Point(200, 250));
	renderer->drawText(&saveGame1, Point(480, 250));
	
	renderer->drawText(&loadGame0, Point(200, 280));
	renderer->drawText(&loadGame1, Point(480, 280));

	renderer->drawText(&quit0, Point(200, 310));
	renderer->drawText(&quit1, Point(480, 310));

	renderer->present();

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

