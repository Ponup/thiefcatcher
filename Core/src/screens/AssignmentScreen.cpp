#include "AssignmentScreen.h"

#include <vector>
using std::vector;

#include <string.h>

#include <FontManager.h>
#include <Text.h>
#include <System.h>

#include "screens/Game.h"
#include "screens/handlers/GameEventHandler.h"

#include "entities/Player.h"
#include "entities/PlayersManager.h"
#include "entities/PlayerCaseManager.h"

#include "utilities/Translator.h"

AssignmentScreen::AssignmentScreen(Window *window) : ComputerScreen(window) {	
	fontInput.load("resources/fonts/FreeSansBold.ttf", 14);
	fontInput.setColor(Color(255, 255, 255));

	input = new InputBox(window, &fontInput, Point(120, 440), Dimension(400, 22));
}

AssignmentScreen::~AssignmentScreen() {
	delete input;
}

bool isValidName(const char *name) {
	if(!name) return false;

	if(strlen(name) < 2) return false;

	return true;
}

PlayerCase *AssignmentScreen::show() {
	addLine(_("Police at the keyboard, please identify yourself:"));
	showLines();

	const char *name = input->get();
	addLine(name);

	while(!isValidName(name)) {
		addLine(_("Your name is not valid. Please type a name with at least two characters:"));
		showLines();

		input->clear();
		
		name = input->get();
		addLine(name);
	}
	
	Player *player = PlayersManager::findByName(name);
	while (!player) {
		addLine(_("Your name does not appear in the files of Interpol. Are you new here? (Y/N):"));
		showLines();

		// readKey() locks the user input
		SDLKey key = readKey();
		
		if (key == SDLK_y || key == SDLK_s) {
			player = PlayersManager::create(name);
			break;
		}

		addLine(_("Please, type your name as it is known at the Interpol:"));
		showLines();

		input->clear();
		
		name= input->get();
		addLine(name);

		player = PlayersManager::findByName(name);
	}

	char l[100];

	memset(l, '\0', 100);
	sprintf(l, _("You has been identified, %s."), player->getName());
	addLine(l);

	memset(l, '\0', 100);
	sprintf(l, _("Your current rank is: %s."), PlayersManager::getRank(*player));

	addLine(l);

	PlayerCase *playerCase = PlayerCaseManager::createRandomCase(*player);

	addLine(" ");
	addLine(_("*** NEWS ***"));
	addLine(" ");

	char line[500];

	memset(line, '\0', 500);
	sprintf(line, _("National treasure stolen in %s."),
			playerCase->currentCountry.getName());
	addLine(line);

	memset(line, '\0', 500);
	sprintf(line, _("The loot has been identified as %s."),
			playerCase->getStolenObject());
	addLine(line);

	memset(line, '\0', 500);
	sprintf(line, _("A %s suspect was seen at the crime scene."),
			playerCase->getCriminal().getSex());
	addLine(line);

	memset(line, '\0', 500);
	sprintf(
			line,
			_("Your mission: To pursue the thief from %s to its hideout and arrest him!"),
			playerCase->currentCountry.getName());
	addLine(line);

	memset(line, '\0', 500);
	sprintf(line, _("You have to arrest the thief before %s."),
			playerCase->endDate->toString("%A %d, %H:%M"));
	addLine(line);

	addLine(" ");

	memset(line, '\0', 500);
	sprintf(line, _("Good luck, %s %s."), PlayersManager::getRank(*player), player->getName());
	addLine(line);

	showLines();

	System::waitUser();
	
	return playerCase;
}

