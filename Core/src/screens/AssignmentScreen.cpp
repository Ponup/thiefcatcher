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

AssignmentScreen::AssignmentScreen(Window *window) : ComputerScreen(window) {	
	fontInput.load("resources/fonts/NotCourierSans-Bold.ttf", 14);
	fontInput.setColor(Color(255, 255, 255));
	//font->setColor(Color(0, 255, 50));

	input = new InputBox(bgSurf, &fontInput, Point(120, 440), Dimension(400, 22));
}

AssignmentScreen::~AssignmentScreen() {
	delete input;
}

bool isValidName( string name ) {
	return ( name.length() > 2 );
}

PlayerCase *AssignmentScreen::show() {
	addLine(_("Police at the keyboard, please identify yourself:"));
	showLines();

	string name = input->get();
	addLine(name);

	while( !isValidName( name ) ) {
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
		int key = readKey();
		
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
			playerCase->getStolenObject());
	addLine(line);

	memset(line, '\0', 500);
	sprintf(line, _("A %s suspect was seen at the crime scene.").c_str(),
		CriminalFormatter::formatGenre( playerCase->getCriminal() ).c_str() );
	addLine(line);

	memset(line, '\0', 500);
	sprintf(
			line,
			_("Your mission: To pursue the thief from %s to its hideout and arrest him!").c_str(),
			playerCase->currentCountry.getName().c_str());
	addLine(line);

	memset(line, '\0', 500);
	sprintf(line, _("You have to arrest the thief before %s.").c_str(),
			playerCase->endDate->toString("%A %d, %H:%M"));
	addLine(line);

	addLine(" ");

	memset(line, '\0', 500);
	sprintf(line, _("Good luck, %s %s.").c_str(), player->getRank().c_str(), player->getName().c_str());
	addLine(line);

	showLines();

	SDL_Event event;
	bool quit = false;
	while(!quit) {
		while(SDL_PollEvent(&event)) {
			quit = (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN || event.type == SDL_QUIT);
		}
		SDL_Delay(10);		
	}
	
	return playerCase;
}

