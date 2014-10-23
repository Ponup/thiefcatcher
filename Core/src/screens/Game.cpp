#include "Game.h"

#include <Random.h>
#include <MediaManager.h>
#include <MathUtil.h>

#include "Vars.h" 

#include "entities/Place.h"

#include "utilities/Translator.h"
#include "components/ConfirmationDialog.h"

#include "screens/Map.h"
#include "screens/PlaceSelector.h"
#include "screens/CountryDrawing.h"
#include "screens/ProfileScreen.h"

#include <utility>
using std::pair;

Game::Game(Window* window_, PlayerCase * playerCase_) :
	window(window_), playerCase(playerCase_) {

	background.load("resources/images/mainwindow_bg.png");
	canvas = new Surface( background.toSDL() );

	clock.setPosition(Point(20, 7));

	Area area(Point(410, 370), Dimension(340, 40));
	backupSurf = canvas->getArea(area);

	timeFont.load("resources/fonts/FreeSansBold.ttf", 22);
	timeFont.setColor(Color(252, 244, 221)); // #FCF4DD

	timeControllerSurf = canvas->getArea(Point(120, 20), Dimension(320, 60));
	timeSurfBackup = canvas->getArea(Point(120, 20), Dimension(320, 60));

	dateTimePosition = Point::Origin;

	currentOption = 0;
	
	state = GS_PLAYING;

	options[0] = new Surface("resources/images/game/button_travel.png");
	options_over[0] = new Surface("resources/images/game/button_travel.png");
	points[0] = Point(416, 402);
	labels[0] = _("Travel");

	options[1] = new Surface("resources/images/game/button_capture.png");
	options_over[1] = new Surface("resources/images/game/button_capture.png");
	points[1] = Point(554, 402);
	labels[1] = _("Capture");

	options[2] = new Surface("resources/images/game/button_places.png");
	options_over[2] = new Surface("resources/images/game/button_places.png");
	points[2] = Point(623, 402);
	labels[2] = _("Places");

	options[3] = new Surface("resources/images/game/button_quit.png");
	options_over[3] = new Surface("resources/images/game/button_quit.png");
	points[3] = Point(691, 402);
	labels[3] = _("Quit");

	Country country = playerCase->getCurrentCountry();
	showCountry(canvas, country);

	updateTime();


	window->drawSurface( canvas );
	window->flip();
}

Game::~Game() {
	delete timeControllerSurf;
	delete timeSurfBackup;

	delete options[0];
	delete options[1];
	delete options[2];
	delete options[3];
	delete options_over[0];
	delete options_over[1];
	delete options_over[2];
	delete options_over[3];

	delete canvas;
}

void Game::updateOption() {
	Font font("resources/fonts/FreeSans.ttf", 14);
	font.setColor(Color(255, 255, 255));

	Area area(Point(410, 370), Dimension(340, 40));
	canvas->drawSurface(backupSurf, Point(410, 370));

	for (int i = 0; i < 4; i++) {
		if (i == currentOption) {
			Text::drawString(labels[i], points[i] - Point(-5, 30), &font, canvas);
			canvas->drawSurface(options[i], points[i]);
		} else {
			canvas->drawSurface(options[i], points[i]);
		}
	}

	window->drawSurface( canvas );
	window->flip();
}

void Game::quitGame() {
	Surface *backup = canvas->getArea( Point::Origin, canvas->getDimension() );

	ConfirmationDialog dialog(window, _("Are you sure you want to abort this case?"));
	int selected = dialog.showGetSelected();
	if (selected == ConfirmationDialog::DIALOG_YES) {
		state = GS_ABORT;
	} else {
		window->drawSurface(backup );
		window->flip();
	}

	delete backup;
}

void Game::update() {
	updateOption();
}

bool Game::isPlaying() {
	return state == GS_PLAYING;
}

GameState Game::getGameState() {
	return state;
}

Window *Game::getWindow() {
	return window;
}

void Game::updateTime() {
	timeControllerSurf->drawSurface( timeSurfBackup );

	Text dayLine(playerCase->currentDate->getDayOfWeekName(), &timeFont);
	Text hourLine(playerCase->currentDate->toString("%H:%M"), &timeFont);

	dayLine.draw(dateTimePosition, timeControllerSurf);
	hourLine.draw(dateTimePosition + Point(0, timeFont.getLineSkip()),
			timeControllerSurf);

	canvas->drawSurface(timeControllerSurf, Point(120, 20));
	canvas->updateArea(Area(Point(120, 20), Dimension(320, 60)));

	clock.draw(*(playerCase->currentDate), canvas);
}

void Game::increaseTime(int hours) {
	for (unsigned char i = 0; i < hours; i++) {
		playerCase->currentDate->increase(1, DateTime::Hour);

		updateTime();

		MediaManager::getInstance().playSound("time.wav");
		SDL_Delay(450);
	}
}

void Game::enterOption() {
	switch (currentOption) {
	case 0:
		optionTravel();
		break;
	case 1:
		optionProfile();
		break;
	case 2:
		optionPlaces();
		break;
	case 3:
		quitGame();
		break;
	}
}

void Game::optionTravel() {
	Surface *backup = canvas->getArea( Point::Origin, canvas->getDimension());
	Country &from = playerCase->getCurrentCountry();

	Map map(window, &from, playerCase->nextCountries);
	int selected = map.getSelection();

	printf("Selected country: %d\n", selected);

	// If the user pressed ESCAPE or RIGHT_BUTTON, then the re-draw must be ignored.
	if (selected != -1) {
		window->drawSurface( &background );
		window->flip();

		Country nextCountry = playerCase->nextCountry();
		Country newCountry = playerCase->nextCountries[selected];

		printf("Next country: %s\n", nextCountry.getName().c_str());
		printf("Current country: %s\n", newCountry.getName().c_str());

		if (newCountry.getID() == nextCountry.getID()) {
			int nextPos = playerCase->getCurrentPosition() + 1;
			printf("Incrementing flight position to %d\n", nextPos);
			playerCase->setCurrentPosition(nextPos);
		}

		int hoursWasted = 3; // TODO calculateHours(*from, (*(playerCase->nextCountries + selected)));
		printf("Time from %s to %s: %d hour(s)\n", from.getName().c_str(), newCountry.getName().c_str(), hoursWasted);
		increaseTime(hoursWasted);

		playerCase->setCurrentCountry(newCountry);
		playerCase->updateCountries();
		playerCase->updateClues();

		showCountry(canvas, newCountry);
	} else {
		window->drawSurface(backup );
		window->flip();
	}

	delete backup;
}

void Game::optionPlaces() {
	Surface *backup = canvas->getArea( Point::Origin, canvas->getDimension());

	int *placesPKazar = Random::nextArray(Vars::listPlacesPK(), 3);
	PlaceSelector placeSelector(window, canvas, placesPKazar);
	int selected = placeSelector.showAndReturn();
	window->drawSurface(backup );
	if (selected == -1) {
		window->flip();
	} else {
		increaseTime(3);

		unsigned int secondsCurrent = playerCase->currentDate->toSeconds();
		unsigned int secondsEnd = playerCase->endDate->toSeconds();

		if(secondsCurrent >= secondsEnd) {
			state = GS_LOST_TIME;
			return;
		} else
		if((secondsEnd - secondsCurrent) / 3600 <= 3) {
			Font *fontWarn = FontManager::getFont("FreeSansBold", 35);
			fontWarn->setColor(Color(0xff, 0, 0));
			Text warn("Only 3 hours left!", fontWarn);
			warn.draw(Point(440, 15), canvas);
			delete fontWarn;
		} else
		if(playerCase->currentPosition == 6) {
			state = playerCase->captureOrderExecuted ? GS_WON : GS_LOST_CAPTURE_ORDER;
			return;
		}
		Place place = PlacesManager::findByPrimaryKey(placesPKazar[selected]);
		delete placesPKazar;

		Surface backup("resources/images/mainwindow_bg.png");
		Surface *b = backup.getArea(Area(Point(310, 145), Dimension( 450, 220)));
		window->drawSurface(b, Point(310, 145));

		Surface *character = place.getCharacterSurface();
		Point characterPosition = Point(318, 250);
		Dimension characterDim = character->getDimension();
		Surface *area = canvas->getArea(characterPosition, characterDim);
		window->drawSurface(character, characterPosition);
		Clue *clue = NULL;
		Country country = playerCase->getCurrentCountry();
		if (country.getID() != playerCase->getLastCountry().getID()) {
			clue = new Clue(_("I don't have any clues! (you are in the wrong country!)"));
		} else {
			clue = playerCase->clues[selected];
		}

		Surface ballonSurf("resources/images/ballon.png");
		window->drawSurface(&ballonSurf, Point(395, 194));

		// Clue drawing
		Font *hintFont = FontManager::getFont("FreeSansBold", 14);
		hintFont->setColor(Color(211, 186, 164)); // #D3BAA4	

		Text description(clue->getMessage(), hintFont);
		description.drawLines(Point(440, 220), Dimension(285, 115), canvas);

		canvas->updateArea(Point(395, 194), ballonSurf.getDimension());
		delete hintFont;

		delete area;
		delete character;
	}
	
	delete backup;
}

void Game::optionProfile() {
	Surface *backup = canvas->getArea( Point::Origin, window->getDimension());

	ProfileScreen profileScreen(window, playerCase);
	profileScreen.run();

	window->drawSurface(backup );
	window->flip();
	
	delete backup;
}

int Game::calculateHours(Country &from, Country &to) {
	vector<Point> path = MathUtil::calculatePath( from.getLatitudeLongitude(), to.getLatitudeLongitude() );
	return int(path.size()/30);
}

