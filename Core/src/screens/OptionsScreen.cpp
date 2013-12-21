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

	font = FontManager::getFont("FreeSansBold", 25);
	font->setColor(Color(63, 36, 18));

	fontValue = FontManager::getFont("FreeSans", 25);
	fontValue->setColor(Color(0, 0, 255));
	
	backgroundSurf = new Surface("resources/images/menu/background.png");

	screenTitle = new Text(_("OPTIONS"), font);
		
	languageLabel = new Text(_("Language"), font);
	musicLabel = new Text(_("Music"), font);
	soundsLabel = new Text(_("Sounds"), font);
	fullscreenLabel = new Text(_("Full screen"), font);

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
	
	//Transitions::slideRL(window, window->getArea(Point(0, 0), Dimension(640, 480)));
}

OptionsScreen::~OptionsScreen() {
	//delete font;
	//delete fontValue;
	
	delete screenTitle;
	delete languageLabel;
	delete languageValue;
	delete musicLabel;
	delete musicValue;
	delete soundsLabel;
	delete soundsValue;
	delete fullscreenLabel;
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
	window->drawSurface(backgroundSurf, Point(0, 0));

	int x = (window->getDimension().getWidth() >> 1) - (screenTitle->getDimension().getWidth() >> 1);
	screenTitle->draw(Point(x, 20), window);
	
	languageLabel->draw(Point(200, 130), window);
	languageValue->draw(Point(480, 130), window);
	musicLabel->draw(Point(200, 160), window);
	musicValue->draw(Point(480, 160), window);
	soundsLabel->draw(Point(200, 190), window);
	soundsValue->draw(Point(480, 190), window);
	fullscreenLabel->draw(Point(200, 220), window);
	fullscreenValue->draw(Point(480, 220), window);
	
	if(update) {
		window->flip();
	}
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
