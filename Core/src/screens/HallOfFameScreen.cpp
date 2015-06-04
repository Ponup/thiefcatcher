#include "HallOfFameScreen.h"

#include <FrameRegulator.h>
#include <FontManager.h>
#include <MediaMusic.h>
#include <Text.h>

#include "Constants.h"
#include "utilities/Translator.h"
#include "entities/PlayersManager.h"

#include "ponup-api/Api.h"
using namespace Ponup;

HallOfFameScreen::HallOfFameScreen( Window *screen ) : screen( screen ), quit( false ) {
}

void HallOfFameScreen::show() {
	Surface background("resources/images/menu/background.png");
	Surface* canvas =new Surface("resources/images/menu/background.png");

	Font headerFont("resources/fonts/gtw.ttf", 45);
	headerFont.setColor(Color(255, 220, 220));
	Text headerText(_("Thief Catcher"), &headerFont);
	headerText.draw(Point(30, 10), &background);

	Font playerFont("resources/fonts/FreeSansBold.ttf", 14);
	playerFont.setColor(Color(0x00, 0x00, 0x00));	

	int columnPos[4] = { 240, 260, 360, 480 };
	string headerNames[] = {
		_("#"), _("Player"), _("Rank"), _("Experience")
	};
	
	int headerY = 140;

	for(int i = 0; i < 4; i++)
		Text::drawString(headerNames[i], Point(columnPos[i], headerY), &playerFont, &background);
	
	int playerY = headerY + 40;

	playerFont.setColor(Color(255, 255, 255));	

	vector<Score> scores = Ponup::Api::getScores( "thiefcatcher" );

	for (unsigned int i = 0; i < scores.size(); i++) {
		Score score = scores.at( i );

		char experience[30];
		memset(experience, 0, 30);
		sprintf(experience, "%d case(s)", score.getGameLevelNumber());

		string playerValues[] = {
			std::to_string(i + 1),
			score.getPlayerName(),
			score.getGameLevel(),
			experience
		};

		Surface icon("resources/icons/award_star_gold_1.png", true);
		background.drawSurface(&icon, Point(210, playerY));

		for(int i = 0; i < 4; i++)
			Text::drawString(playerValues[i].c_str(), Point(columnPos[i], playerY), &playerFont, &background); 

		playerY += playerFont.getLineSkip();
	}

	canvas->drawSurface(&background);	
	screen->drawSurface(canvas);
	screen->flip();
	
	MediaMusic sound("resources/sounds/fireworks.aif");
	sound.play();

	FrameRegulator fr(120);
	fr.setUp();
	
	while (!quit) {
		captureEvents();

		if( sound.isPlaying() ) sound.fadeOut();

		canvas->drawSurface(&background);
		screen->drawSurface(canvas);
		screen->flip();
		
		fr.regulate();
	}

	if( sound.isPlaying() )	
		sound.stop();
}

void HallOfFameScreen::onKeyDown(SDL_KeyboardEvent e) {
	quit = true;
}

void HallOfFameScreen::onKeyUp(SDL_KeyboardEvent e) {
	
}

void HallOfFameScreen::onMouseButtonDown(SDL_MouseButtonEvent e) {
	quit = true;
}

void HallOfFameScreen::onMouseButtonUp(SDL_MouseButtonEvent e) {
	
}

void HallOfFameScreen::onMouseMotion(SDL_MouseMotionEvent e) {
	
}

