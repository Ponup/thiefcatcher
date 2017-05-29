#include "AssignmentScreen.h"

#include <vector>
using std::vector;

#include <string.h>

#include <FontManager.h>
#include <Text.h>

#include "screens/Game.h"
#include "screens/handlers/GameEventHandler.h"

#include "entities/Player.h"
#include "entities/PlayersManager.h"
#include "entities/PlayerCaseManager.h"
#include "entities/format/CriminalFormatter.h"

#include "utilities/Translator.h"

AssignmentScreen::AssignmentScreen(Renderer* renderer) : ComputerScreen(renderer) {
    fontInput.load("resources/fonts/NotCourierSans-Bold.ttf", 14);
    fontInput.setColor(Color(255, 255, 255));

    input = new InputBox(&fontInput, Point(120, 440), Dimension(400, 22));
}

AssignmentScreen::~AssignmentScreen() {
    delete input;
}

bool isValidName(const string& name) {
    return (name.length() > 2);
}

PlayerCase *AssignmentScreen::show() {
    addLine(_("Police at the keyboard, please identify yourself:"));
    showLines();

    bool quitted = false;
    string name = askName(quitted);
    if (quitted) {
        return nullptr;
    }

    Player *player = PlayersManager::findByName(name);
    while (!player) {
        addLine(_("Your name does not appear in the files of Interpol. Are you new here? (Y/N):"));
        showLines();

        // readKey() locks the user input
        int key = readKey();
        if (key == SDLK_y || key == SDLK_s) {
            if ((player = PlayersManager::create(name))) {
                break;
            }
        }

        addLine(_("Please, type your name as it is known at the Interpol:"));
        showLines();

        input->clear();

        name = askName(quitted);
        if (quitted) {
            return nullptr;
        }
        addLine(name);

        player = PlayersManager::findByName(name);
    }

    char l[100];

    memset(l, '\0', 100);
    sprintf(l, _("You has been identified, %s.").c_str(), player->getName().c_str());
    addLine(l);

    memset(l, '\0', 100);
    sprintf(l, _("Your current rank is: %s.").c_str(), player->getRank().c_str());

    addLine(l);

    PlayerCase *playerCase = PlayerCaseManager::createRandomCase(*player);

    addLine(" ");
    addLine(_("*** NEWS ***"));
    addLine(" ");

    char line[500];

    memset(line, '\0', 500);
    sprintf(line, _("National treasure stolen in %s.").c_str(),
            playerCase->currentCountry.getName().c_str());
    addLine(line);

    memset(line, '\0', 500);
    sprintf(line, _("The loot has been identified as %s.").c_str(),
            playerCase->getStolenObject().c_str());
    addLine(line);

    memset(line, '\0', 500);
    sprintf(line, _("A %s suspect was seen at the crime scene.").c_str(),
            CriminalFormatter::formatGenre(playerCase->getCriminal()).c_str());
    addLine(line);

    memset(line, '\0', 500);
    sprintf(
            line,
            _("Your mission: To pursue the thief from %s to its hideout and arrest him!").c_str(),
            playerCase->currentCountry.getName().c_str());
    addLine(line);

    memset(line, '\0', 500);
    sprintf(line, _("You have to arrest the thief before %s.").c_str(),
            playerCase->endDate->toString("%A %d, %H:%M").c_str());
    addLine(line);

    addLine(" ");

    memset(line, '\0', 500);
    sprintf(line, _("Good luck, %s %s.").c_str(), player->getRank().c_str(), player->getName().c_str());
    addLine(line);

    showLines();

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            quit = (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN || event.type == SDL_QUIT);
        }
        SDL_Delay(10);
    }

    return playerCase;
}

string AssignmentScreen::askName(bool &quitted) {
    string name;

    SDL_Event ev;
    bool keepLooping = false;

    while (!keepLooping) {
        if (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                keepLooping = quitted = true;
            } else if (ev.type == SDL_KEYDOWN) {
                SDL_Keycode keyCode = ev.key.keysym.sym;
                if (keyCode == SDLK_ESCAPE) {
                    keepLooping = quitted = true;
                } else if (keyCode == SDLK_RETURN) {
                    name = input->getText();
                    addLine(name);

                    if (!isValidName(name)) {
                        addLine(_("Your name is not valid. Please type a name with at least two characters:"));
                        input->clear();
                    } else {
                        keepLooping = true;
                    }

                    showLines();
                } else {
                    input->putChar(keyCode);
                }
            }
        }
        SDL_Delay(30);
    }

    return name;
}

