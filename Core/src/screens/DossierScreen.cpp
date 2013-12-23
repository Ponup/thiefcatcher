#include "DossierScreen.h"

#include <string>
using std::string;

#include <Text.h>
#include <FontManager.h>
#include <FrameRegulator.h>

#include "utilities/Translator.h"
#include "ui/Transitions.h"
#include "entities/CriminalsManager.h"
#include "entities/format/CriminalFormatter.h"

DossierScreen::DossierScreen(Window *window_) : window(window_) {
	criminals = CriminalsManager::findAll();

	sensAreas.addArea(Area(Point(28, 511), Dimension(61, 61)));
	
	index = 0;
	quit = false;

	fontName.load("resources/fonts/FreeSansBold.ttf", 30);
	fontName.setColor(Color(255, 200, 100));

	font.load("resources/fonts/FreeSansBold.ttf", 18);

	backgroundSurf = new Surface("resources/images/dossiers/background.png");

	Font headerFont("resources/fonts/gtw.ttf", 45);
	headerFont.setColor(Color(255, 220, 220));
	Text headerText(_("Thief Catcher"), &headerFont);
	headerText.draw(Point(30, 10), backgroundSurf);

	Text text1(_("Genre"), &font);
	text1.draw(Point(300 - text1.getDimension().getWidth(), 250), backgroundSurf);

	Text text3(_("Hobby"), &font);
	text3.draw(Point(300 - text3.getDimension().getWidth(), 300), backgroundSurf);

	Text text5(_("Hair"), &font);
	text5.draw(Point(300 - text5.getDimension().getWidth(), 345), backgroundSurf);

	Text text7(_("Feature"), &font);
	text7.draw(Point(300 - text7.getDimension().getWidth(), 390), backgroundSurf);
	
	updateScreen(false);
	
	window->flip();
}

DossierScreen::~DossierScreen() {
	delete backgroundSurf;
}

void DossierScreen::show() {
	FrameRegulator fr(120);
	fr.setUp();

	while (!quit) {
		captureEvents();
		updateScreen(true);
		fr.regulate();
	}
}

void DossierScreen::updateScreen(bool update) {
	Criminal &criminal = criminals->at(index);

	char path[50];
	memset(path, '\0', 50);
	sprintf(path, "data/criminals/%d.jpg", criminal.getID());

	window->drawSurface(backgroundSurf, Point(0, 0));

	Surface avatar(path, false);
	window->drawSurface(&avatar, Point(460, 90));

	Text text0(criminal.getName(), &fontName);
	text0.draw(Point(140, 140), window);

	Text text2( CriminalFormatter::formatGenre( criminal ), &font);
	text2.draw(Point(320, 250), window);

	Text text4(criminal.getHobby(), &font);
	text4.draw(Point(320, 300), window);

	Text text6(criminal.getHair(), &font);
	text6.draw(Point(320, 345), window);

	Text text8(criminal.getFeature(), &font);
	text8.draw(Point(320, 390), window);

	if(update) {
		window->flip();
	}
}

void DossierScreen::onQuit(SDL_QuitEvent e) {

}

void DossierScreen::onMouseMotion(SDL_MouseMotionEvent e) {

}

void DossierScreen::onMouseButtonDown(SDL_MouseButtonEvent e) {
	if(sensAreas.resolve(e.x, e.y) != -1) {
		quit = true;
	}
	if (e.button == SDL_BUTTON_RIGHT) {
		quit = true;
	}
}

void DossierScreen::onMouseButtonUp(SDL_MouseButtonEvent e) {

}

void DossierScreen::onKeyDown(SDL_KeyboardEvent e) {
	switch (e.keysym.sym) {
	case SDLK_RIGHT:
		if (index + 1 < static_cast<int>(criminals->size())) {
			index++;
		}
		break;
	case SDLK_LEFT:
		if (index > 0) {
			index--;
		}
		break;
	case SDLK_ESCAPE:
		quit = true;
		break;
	default:
		break;
	}
}

void DossierScreen::onKeyUp(SDL_KeyboardEvent e) {

}
