#include "OptionsScreen.h"

enum {
	LANG_ENGLISH = 0,
	LANG_SPANISH,
	LANG_CATALAN,
	NUM_LANGUAGES
};

const char LANGUAGES[NUM_LANGUAGES][20] = { "Spanish", "English", "Catalan" };

OptionsScreen::OptionsScreen(Window *window_) : window(window_) {
	quit = false;

	configurator = Configurator::getInstance();
	configurator.init();

	languageIndex = 0;

	Font *font = FontManager::getFont("FreeSansBold", 25);
	font->setColor(Color(63, 36, 18));

	fontValue = FontManager::getFont("FreeSans", 25);
	fontValue->setColor(Color(0, 0, 255));
	
	backgroundSurf = new Surface("resources/images/menu/background.png");

	Font headerFont("resources/fonts/gtw.ttf", 45);
	headerFont.setColor(Color(255, 220, 220));
	Text headerText(_("Thief Catcher"), &headerFont);
	headerText.draw(Point(30, 10), backgroundSurf);

	headerFont.setColor(Color(63, 36, 18));
	Text screenTitle(_("Options"), &headerFont);
	int x = window->getDimension().w - screenTitle.getDimension().w - 30;
	screenTitle.draw(Point(x, 10), backgroundSurf);
		
	Text languageLabel(_("Language"), font);
	Text musicLabel(_("Music"), font);
	Text soundsLabel(_("Sounds"), font);
	Text fullscreenLabel(_("Full screen"), font);

	languageLabel.draw(Point(200, 130), backgroundSurf);
	musicLabel.draw(Point(200, 160), backgroundSurf);
	soundsLabel.draw(Point(200, 190), backgroundSurf);
	fullscreenLabel.draw(Point(200, 220), backgroundSurf);

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
	
	delete backgroundSurf;
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
	if( !update ) {
		return;
	}

	Surface *canvas = new Surface(backgroundSurf->toSDL());
	
	languageValue->draw(Point(480, 130), canvas);
	musicValue->draw(Point(480, 160), canvas);
	soundsValue->draw(Point(480, 190), canvas);
	fullscreenValue->draw(Point(480, 220), canvas);
	
	window->drawSurface( canvas );
	delete canvas;

	window->flip();
}

void OptionsScreen::onQuit(SDL_QuitEvent e) {

}

void OptionsScreen::onMouseMotion(SDL_MouseMotionEvent e) {

}

void OptionsScreen::onMouseButtonDown(SDL_MouseButtonEvent e) {
	if (e.button == SDL_BUTTON_RIGHT) {
		quit = true;
	} else {
		int resolved = sensAreas.resolve(e.x, e.y);
		if (resolved != -1) {
			switch (resolved) {
			case 0: {
				if (languageIndex + 1 < NUM_LANGUAGES) {
					languageIndex++;
				} else {
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
				window->toggleFullScreen();
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
