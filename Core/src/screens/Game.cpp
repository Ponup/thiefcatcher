#include "Game.h"

#include <Random.h>
#include <MediaManager.h>
#include <MathUtil.h>
#include <TextUtils.h>
using Kangaroo::TextUtils;

#include "Vars.h" 

#include "entities/Place.h"

#include "utilities/Translator.h"
#include "components/ConfirmationDialog.h"

#include "screens/Map.h"
#include "screens/PlaceSelector.h"
#include "screens/CountryDrawing.h"
#include "screens/ProfileScreen.h"

#include "entities/ClueFactory.h"

#include <utility>
using std::pair;

Game::Game(Window* window, PlayerCase* playerCase) :
window(window),
renderer(window->renderer),
backgroundTexture(window->renderer, "resources/images/mainwindow_bg.png"),
playerCase(playerCase),
activeClue(nullptr),
normalCursor(SDL_SYSTEM_CURSOR_ARROW),
handCursor(SDL_SYSTEM_CURSOR_HAND) {

    clock = new Clock(window);
    clock->setPosition(Point(20, 7));

    timeFont.load("resources/fonts/FreeSansBold.ttf", 22);
    timeFont.setColor(Color(252, 244, 221)); // #FCF4DD

    dateTimePosition = Point::Origin;

    currentOption = 0;

    state = GameState::Playing;

    buttons[0] = new SquareButton(window->renderer, "resources/images/game/button_travel.png", "resources/images/game/button_travel.png", Point(416, 402), _("Travel"));
    buttons[1] = new SquareButton(window->renderer, "resources/images/game/button_capture.png", "resources/images/game/button_capture.png", Point(554, 402), _("Capture"));
    buttons[2] = new SquareButton(window->renderer, "resources/images/game/button_places.png", "resources/images/game/button_places.png", Point(623, 402), _("Places"));
    buttons[3] = new SquareButton(window->renderer, "resources/images/game/button_quit.png", "resources/images/game/button_quit.png", Point(691, 402), _("Quit"));

    drawScene();
}

Game::~Game() {
    for (int i = 0; i < 4; i++) {
        delete buttons[i];
    }
}

void Game::drawPlacesArea() {
    Font font("resources/fonts/FreeSans.ttf", 14);
    font.setColor(Color(255, 255, 255));

    for (int i = 0; i < 4; i++) {
        if (i == currentOption) {
            Text optionLabel(buttons[i]->getLabel(), &font);
            renderer.drawText(&optionLabel, buttons[i]->getPosition() - Point(-5, 30));
            renderer.drawTexture(buttons[i]->getImageOver(), buttons[i]->getPosition());
        } else {
            renderer.drawTexture(buttons[i]->getImage(), buttons[i]->getPosition());
        }
    }
}

void Game::quitGame() {
    ConfirmationDialog dialog(window, _("Are you sure you want to abort this case?"));
    int selected = dialog.showGetSelected();
    if (selected == ConfirmationDialog::DIALOG_YES) {
        state = GameState::Abort;
    }
}

void Game::update() {
    drawScene();
}

bool Game::isPlaying() const {
    return state == GameState::Playing;
}

GameState Game::getGameState() const {
    return state;
}

Window *Game::getWindow() {
    return window;
}

void Game::drawTimeArea() {
    Point basePosition(120, 20);
    Text dayLine(playerCase->currentDate->getDayOfWeekName(), &timeFont);
    Text hourLine(playerCase->currentDate->toString("%H:%M"), &timeFont);

    renderer.drawText(&dayLine, basePosition + dateTimePosition);
    renderer.drawText(&hourLine, basePosition + dateTimePosition + Point(0, timeFont.getLineSkip()));

    clock->draw(*(playerCase->currentDate), &renderer);
}

void Game::increaseTime(int hours) {
    for (unsigned char i = 0; i < hours; i++) {
        playerCase->currentDate->increase(1, DateTime::Hour);

        drawScene();

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
    Country &from = playerCase->getCurrentCountry();

    Map map(&renderer, &from, playerCase->nextCountries);
    int selected = map.getSelection();

    // If the user pressed ESCAPE or RIGHT_BUTTON, then the re-draw must be ignored.
    if (selected != -1) {
        Country nextCountry = playerCase->nextCountry();
        Country newCountry = playerCase->nextCountries[selected];

        if (newCountry == nextCountry) {
            int nextPos = playerCase->getCurrentPosition() + 1;
            playerCase->setCurrentPosition(nextPos);
        }

        int hoursWasted = calculateHours(from, (*(playerCase->nextCountries + selected)));
        increaseTime(hoursWasted);

        playerCase->setCurrentCountry(newCountry);
        playerCase->updateCountries();
        playerCase->updateClues();

        activeClue = nullptr;
    }

    drawScene();
}

void Game::optionPlaces() {
    vector<Place> randomPlaces = PlacesManager::findRandom(3);
    PlaceSelector placeSelector(&renderer, NULL, randomPlaces);
    int selected = placeSelector.showAndReturn();
    if (selected == -1) {
        return;
    }

    increaseTime(3);

    time_t secondsCurrent = playerCase->currentDate->toSeconds();
    time_t secondsEnd = playerCase->endDate->toSeconds();

    if (secondsCurrent >= secondsEnd) {
        state = GameState::LostTimeout;
        return;
    } else {
        if ((secondsEnd - secondsCurrent) / 3600 <= 3) {
            Font *fontWarn = FontManager::getFont("FreeSansBold", 35);
            fontWarn->setColor(Color(0xff, 0, 0));
            Text warn("Only 3 hours left!", fontWarn);
            renderer.drawText(&warn, Point(440, 15));
        } else
            if (playerCase->currentPosition == playerCase->itinerary.size() - 1) {
            state = playerCase->captureOrderExecuted ? GameState::Won : GameState::LostEscaped;
            return;
        }
    }
    place = randomPlaces[selected];

    Country country = playerCase->getCurrentCountry();
    if (country.getID() != playerCase->getLastCountry().getID()) {
        ClueFactory clueFactory;
        activeClue = clueFactory.createWrongCountryClue();
    } else {
        activeClue = playerCase->clues[selected];
    }
}

void Game::optionProfile() {
    ProfileScreen profileScreen(&renderer, playerCase);
    profileScreen.run();

    drawScene();
}

int Game::calculateHours(Country &from, Country &to) {
    vector<Point> path = MathUtil::calculatePath(from.getCoordinates().toPair(), to.getCoordinates().toPair());
    int hours = int(path.size() / 30);
    return hours > 0 ? hours : 1;
}

void Game::drawScene() {
    bool hasClue = activeClue != nullptr;

    renderer.drawTexture(&backgroundTexture);

    drawTimeArea();
    drawCountry(&renderer, playerCase->getCurrentCountry(), !hasClue);
    if (hasClue) {
        Texture ballonSurf(renderer.internal, "resources/images/ballon.png");
        renderer.drawTexture(&ballonSurf, Point(395, 194));

        Texture characterTexture(renderer.internal, "resources/images/places/" + place.getName() + "_character.png");
        Point characterPosition = Point(318, 250);
        renderer.drawTexture(&characterTexture, characterPosition);

        // Clue drawing
        Font *hintFont = FontManager::getFont("FreeSansBold", 14);
        hintFont->setColor(Color(211, 186, 164)); // #D3BAA4	

        Text description(activeClue->getMessage(), hintFont);
        TextUtils textUtils;
        textUtils.drawLines(&renderer, description, Point(440, 220), Dimension(285, 115));
    }
    drawPlacesArea();

    renderer.present();
}