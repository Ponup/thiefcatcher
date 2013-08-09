#include "HallOfFameScreen.h"

#include <FrameRegulator.h>
#include <FontManager.h>
#include <MediaMusic.h>
#include <Text.h>

#include "Constants.h"
#include "utilities/fx/FireworksPS.h"
#include "utilities/Translator.h"
#include "entities/PlayersManager.h"
#include "ui/Transitions.h"

HallOfFameScreen::HallOfFameScreen(Surface *screen_) : screen(screen_) {
	quit = false;
}

void HallOfFameScreen::show() {
	Surface background("resources/images/hall_of_fame_background.png");
	screen->drawSurface(&background, Point(0, 0));	
	
	Font playerFont("resources/fonts/FreeSansBold.ttf", 14);
	playerFont.setColor(Color(255, 255, 0));	

	int columnPos[4] = { 60, 80, 180, 300 };
	const char *headerNames[] = {
		_("#"), _("Player"), _("Rank"), _("Experience")
	};
	
	int headerY = 70;

	for(int i = 0; i < 4; i++)
		Text::drawString(headerNames[i], Point(columnPos[i], headerY), &playerFont, screen);

	playerFont.setColor(Color(255, 255, 255));	
	
	int playerY = headerY + 40;
	vector<Player> players = PlayersManager::findTop10();
	for (unsigned int i = 0; i < players.size(); i++) {
		Player player = (Player)players.at(i);

		char top[3];
		memset(top, 0, 3);
		sprintf(top, "%2d", i + 1);
		char experience[30];
		memset(experience, 0, 30);
		sprintf(experience, "%d case(s)", player.getResolved());

		const char *playerValues[] = {
			top,
			player.getName(),
			PlayersManager::getRank(player),
			experience
		};

		Surface icon("resources/icons/award_star_gold_1.png", true);
		screen->drawSurface(&icon, Point(40, playerY));

		for(int i = 0; i < 4; i++)
			Text::drawString(playerValues[i], Point(columnPos[i], playerY), &playerFont, screen); 

		playerY += playerFont.getLineSkip();
	}

	players.clear();
	
	// Transitions::slideRL(screen, screen->getArea());
	screen->flip();
	
	Surface *backup = screen->getArea(Point(0, 0), screen->getDimension());

	FireworksPS fireworks;
	
	MediaMusic sound("resources/sounds/fireworks.aif");
	sound.play();

	FrameRegulator fr(120);
	fr.setUp();
	
	while (!quit) {
		captureEvents();
		screen->drawSurface(backup, Point(0, 0));
		fireworks.update();
		fireworks.draw(screen);
		screen->flip();
		
		fr.regulate();
	}
	
	sound.stop();
	
	delete backup;
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

