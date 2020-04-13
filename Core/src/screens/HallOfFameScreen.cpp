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

HallOfFameScreen::HallOfFameScreen(Renderer* renderer) : renderer(renderer), quit(false) {
}

void HallOfFameScreen::show() {
	Texture backgroundTexture(renderer->internal, "resources/images/menu/background.png");
	renderer->drawTexture(&backgroundTexture);

	Font headerFont("resources/fonts/gtw.ttf", 45);
	headerFont.setColor(Color(255, 220, 220));
	Text headerText(_("Thief Catcher"), &headerFont);
	renderer->drawText(&headerText, Point(30, 10));

	Font playerFont("resources/fonts/FreeSansBold.ttf", 14);
	playerFont.setColor(Color(0x00, 0x00, 0x00));

	int columnPos[4] = { 240, 260, 360, 480 };
	string headerNames[] = {
		_("#"), _("Player"), _("Rank"), _("Experience")
	};

	int headerY = 140;

	for (int i = 0; i < 4; i++) {
		Text header(headerNames[i], &playerFont);
		renderer->drawText(&header, Point(columnPos[i], headerY));
	}

	int playerY = headerY + 40;

	playerFont.setColor(Color(255, 255, 255));

	vector<Score> scores = Ponup::Api::getScores("thiefcatcher");

	for (unsigned int i = 0; i < scores.size(); i++) {
		Score score = scores.at(i);

		char experience[30];
		memset(experience, 0, 30);
		sprintf(experience, "%d case(s)", score.getGameLevelNumber());

		string playerValues[] = {
			std::to_string(i + 1),
			score.getPlayerName(),
			score.getGameLevel(),
			experience
		};

		Texture icon(renderer->internal, "resources/icons/award_star_gold_1.png");
		renderer->drawTexture(&icon, Point(210, playerY));

		for (int i = 0; i < 4; i++) {
			Text value(playerValues[i].c_str(), &playerFont);
			renderer->drawText(&value, Point(columnPos[i], playerY));
		}

		playerY += playerFont.getLineSkip();
	}

	renderer->present();

	MediaMusic sound("resources/sounds/applauses.mp3");
	sound.play();

	FrameRegulator fr(120);
	fr.setUp();

	while (!quit) {
		captureEvents();

		fr.regulate();
	}

	if (sound.isPlaying()) {
		sound.fadeOut(1);
	}
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

