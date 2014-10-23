#include "MenuScreen.h"

#include <MediaMusic.h>
#include "components/ConfirmationDialog.h"
#include "entities/PlayersManager.h"

#include "ui/widgets/Menu.h"

#include "screens/Game.h"
#include "screens/handlers/GameEventHandler.h"
#include "screens/ComputerScreen.h"
#include "screens/AssignmentScreen.h"
#include "screens/HelpScreen.h"
#include "screens/IntroScreen.h"
#include "screens/OptionsScreen.h"
#include "screens/DossierScreen.h"
#include "screens/HallOfFameScreen.h"

void MenuScreen::show() {
	Menu menu(window);
	menu.setSelectedItem(0);
	menu.addItem(_("New game"));
	menu.addItem(_("Dossiers"));
	menu.addItem(_("Hall of fame"));
	menu.addItem(_("Options"));
	menu.addItem(_("Help"));
	menu.addItem(_("Quit"));

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
			AssignmentScreen assigScreen(window);
			PlayerCase *playerCase = assigScreen.show();
			if(playerCase == NULL) continue;

			Game game(window, playerCase);
			GameEventHandler gameEventHandler(&game);
			while (game.isPlaying()) {
				gameEventHandler.captureEvents();
				game.update();
			}

			Player player = playerCase->getPlayer();

			ComputerScreen screen(window);
			switch(game.getGameState()) {
				case GS_WON:
					PlayersManager::updatePlayer(player);
					screen.addLine(_("Congratulations, you have won the case and promoted!"));
					break;
				case GS_ABORT:
					screen.addLine(_("The mission has been aborted, fortunately was all a hoax."));
					break;
				case GS_LOST_TIME:
					screen.addLine(_("You took a long time and the robber has escaped. Try again with another case."));
					break;
				case GS_LOST_CAPTURE_ORDER:
					screen.addLine(_("What a shame! You had cornered the thief but escaped because they had no warrant. Try with another case."));
					break;
				default:
					screen.addLine(_("Internal error. Oopss."));
			}
			screen.showLines();
			screen.waitKey();
			} break;
		case 1: {
			DossierScreen dossierScreen(window);
			dossierScreen.show();
			} break;
		case 2: {
			HallOfFameScreen hallOfFame(window);
			hallOfFame.show();
			} break;
		case 3: {
			OptionsScreen optionsScreen(window);
			optionsScreen.show();
			} break;
		case 4: {
			HelpScreen helpScreen(window);
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

