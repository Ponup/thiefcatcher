#include "MenuScreen.h"

#include <MediaMusic.h>
#include "components/ConfirmationDialog.h"
#include "entities/PlayersManager.h"

#include "screens/Game.h"
#include "screens/handlers/GameEventHandler.h"
#include "screens/ComputerScreen.h"
#include "screens/AssignmentScreen.h"
#include "screens/HelpScreen.h"
#include "screens/IntroScreen.h"
#include "screens/OptionsScreen.h"
#include "screens/DossierScreen.h"
#include "screens/HallOfFameScreen.h"
#include "screens/GameOverScreen.h"

#include <Renderer.h>

using Kangaroo::Renderer;

MenuScreen::MenuScreen(Window *window, const Configurator *configurator) :
	window(window),
	configurator(configurator),
	menu(window) {

	menu.setSelectedItem(0);
	menu.addItem(_("New game"));
	menu.addItem(_("Dossiers"));
	menu.addItem(_("Hall of fame"));
	menu.addItem(_("Options"));
	menu.addItem(_("Help"));
	menu.addItem(_("Quit"));
}

void MenuScreen::show() {
	Renderer renderer(window->renderer);

	MediaMusic music("resources/sounds/weird_loop.wav");
	if (configurator->isPlayMusic())
		music.play();

	bool quit = false;
	int optionSelected = 0;
	while (!quit) {
		menu.reset();
		optionSelected = menu.getSelectedItem();

		switch (optionSelected) {
		case 0: {
			AssignmentScreen assigScreen(&renderer);
			PlayerCase *playerCase = assigScreen.show();
			if (playerCase == nullptr) continue;

			Game game(window, playerCase);
			GameEventHandler gameEventHandler(&game);
			while (game.isPlaying()) {
				gameEventHandler.captureEvents();
				game.update();
			}

			GameOverScreen gameOverScreen(&renderer, &game, playerCase);
			gameOverScreen.show();
		} break;
		case 1: {
			DossierScreen dossierScreen(window);
			dossierScreen.show();
		} break;
		case 2: {
			HallOfFameScreen hallOfFame(&renderer);
			hallOfFame.show();
		} break;
		case 3: {
			OptionsScreen optionsScreen(&renderer);
			optionsScreen.show();
		} break;
		case 4: {
			HelpScreen helpScreen(&renderer);
			helpScreen.show();
		} break;
		case 5: {
			ConfirmationDialog dialog(window, _("Are you sure you want to quit?"));
			int selected = dialog.showGetSelected();
			quit = (selected == ConfirmationDialog::DIALOG_YES);
		} break;
		}
	}
}

