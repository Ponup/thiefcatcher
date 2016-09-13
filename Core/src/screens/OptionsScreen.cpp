#include "OptionsScreen.h"

#include "Game.h"

enum {
	LANG_ENGLISH = 0,
	LANG_SPANISH,
	LANG_CATALAN,
	NUM_LANGUAGES
};

const char LANGUAGES[NUM_LANGUAGES][20] = { "Spanish", "English", "Catalan" };

OptionsScreen::OptionsScreen(Renderer* renderer) :
	renderer(renderer),
	backgroundTexture(renderer->internal, "resources/images/menu/background.png"),
	normalCursor(SDL_SYSTEM_CURSOR_ARROW),
	handCursor(SDL_SYSTEM_CURSOR_HAND)
	{
	quit = false;

	configurator = Configurator::getInstance();
	configurator.init();

	languageIndex = 0;

	fontValue = FontManager::getFont("FreeSans", 25);
	fontValue->setColor(Color(0, 0, 255));

	languageValue = new Text();
	languageValue->setFont(fontValue);
	musicValue = new Text();
	musicValue->setFont(fontValue);
	soundsValue = new Text();
	soundsValue->setFont(fontValue);
	fullscreenValue = new Text();
	fullscreenValue->setFont(fontValue);

	updateValues();

	sensAreas.addArea(Point(480, 130), languageValue->getDimension());
	sensAreas.addArea(Point(480, 160), musicValue->getDimension());
	sensAreas.addArea(Point(480, 190), soundsValue->getDimension());
	sensAreas.addArea(Point(480, 220), fullscreenValue->getDimension());

	updateScreen(false);
}

OptionsScreen::~OptionsScreen() {
	delete languageValue;
	delete musicValue;
	delete soundsValue;
	delete fullscreenValue;
}

void OptionsScreen::show() {
	while (!quit) {
		captureEvents();
		updateValues();
		updateScreen(true);
		SDL_Delay(30);
	}

	configurator.save();
}

void OptionsScreen::updateValues() {
	languageValue->setText(LANGUAGES[languageIndex]);
	musicValue->setText(configurator.isPlayMusic() ? _("On") : _("Off"));
	soundsValue->setText(configurator.isPlaySounds() ? _("On") : _("Off"));
	fullscreenValue->setText(configurator.isFullScreen() ? _("On") : _("Off"));
}

void OptionsScreen::updateScreen(bool update) {
	if (!update) {
		return;
	}

	renderer->drawTexture(&backgroundTexture);

	Font *font = FontManager::getFont("FreeSansBold", 25);
	font->setColor(Color(63, 36, 18));

	Font headerFont("resources/fonts/gtw.ttf", 45);
	headerFont.setColor(Color(255, 220, 220));
	Text headerText(_("Thief Catcher"), &headerFont);
	renderer->drawText(&headerText, Point(30, 10));

	headerFont.setColor(Color(63, 36, 18));
	Text screenTitle(_("Options"), &headerFont);
	int x = Game::Width - screenTitle.getDimension().w - 30;
	renderer->drawText(&screenTitle, Point(x, 10));

	Text languageLabel(_("Language"), font);
	Text musicLabel(_("Music"), font);
	Text soundsLabel(_("Sounds"), font);
	Text fullscreenLabel(_("Full screen"), font);

	renderer->drawText(&languageLabel, Point(200, 130));
	renderer->drawText(&musicLabel, Point(200, 160));
	renderer->drawText(&soundsLabel, Point(200, 190));
	renderer->drawText(&fullscreenLabel, Point(200, 220));

	renderer->drawText(languageValue, Point(480, 130));
	renderer->drawText(musicValue, Point(480, 160));
	renderer->drawText(soundsValue, Point(480, 190));
	renderer->drawText(fullscreenValue, Point(480, 220));

	renderer->present();
}

void OptionsScreen::onQuit(SDL_QuitEvent e) {

}

void OptionsScreen::onMouseMotion(SDL_MouseMotionEvent e) {
	int resolved = sensAreas.resolve(e.x, e.y);
	if (resolved == -1)
		normalCursor.applyToWindow();
	else
		handCursor.applyToWindow();
}

void OptionsScreen::onMouseButtonDown(SDL_MouseButtonEvent e) {
	if (e.button == SDL_BUTTON_RIGHT) {
		quit = true;
	}
	else {
		int resolved = sensAreas.resolve(e.x, e.y);
		if (resolved != -1) {
			switch (resolved) {
			case 0: {
				if (languageIndex + 1 < NUM_LANGUAGES) {
					languageIndex++;
				}
				else {
					languageIndex = 0;
				}
				const char *language = NULL;
				switch (languageIndex) {
				case LANG_ENGLISH:
					language = "en.utf8";
					break;
				case LANG_SPANISH:
					language = "es.utf8";
					break;
				case LANG_CATALAN:
					language = "ca.utf8";
					break;
				}
				configurator.setLanguage(language);
			}
					break;
			case 1:
				configurator.setPlayMusic(!configurator.isPlayMusic());
				break;
			case 2:
				configurator.setPlaySounds(!configurator.isPlaySounds());
				break;
			case 3:
				configurator.setFullScreen(!configurator.isFullScreen());
				//window->toggleFullScreen();
				break;
			}
		}
	}
}

void OptionsScreen::onMouseButtonUp(SDL_MouseButtonEvent e) {

}

void OptionsScreen::onKeyDown(SDL_KeyboardEvent e) {
	if (e.keysym.sym == SDLK_ESCAPE) {
		quit = true;
	}
}

void OptionsScreen::onKeyUp(SDL_KeyboardEvent e) {

}
