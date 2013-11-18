
#include <signal.h>

#include <SDL.h>

#include <Services.h>
#include <CoreService.h>
#include <MixerService.h>
#include <FontService.h>
#include <MediaMusic.h>
#include <Database.h>

#include "Constants.h"
#include "Vars.h"

#include "entities/PlayersManager.h"

#include "utilities/Updater.h"
#include "utilities/Translator.h"

#include "components/ConfirmationDialog.h"
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

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void onInterrupt(int code) {
	printf("Game interrupted by the user (code: %d). Exiting.\n", code);
	exit(1);
}

int main(int argc, char * argv[]) {

	signal(SIGINT, onInterrupt);

	Services services;
	services.addService(new CoreService(CoreService::VIDEO | CoreService::AUDIO));
	services.addService(new MixerService(AUDIO_S16SYS /*IX_DEFAULT_FREQUENCY*/, 2));
	services.addService(new FontService());
	services.init();

	{
	if (false) { // Updater::existsNewVersion(GAME_VERSION)) {
		printf("%s\n", _("A new version of 'Where the hell' is ready to download!"));
	}

	Configurator configurator = Configurator::getInstance();

	try {
		configurator.init();
	} catch (std::runtime_error &error) {
		fprintf( stderr, "%s\n", error.what() );
		exit(1);
	}

	Translator::init(configurator.getLanguage());

	Window
			*window=
					new Window(_("Thief Catcher"), GAME_WINDOW_W, GAME_WINDOW_H, "resources/logo/thief_256.png", configurator.isFullScreen());

	try {
		Database::init( "data/game.db" );
		Vars::init();
	} catch (std::runtime_error &error) {
		fprintf(stderr, "ERROR: %s\n", error.what());
		exit(1);
	}

	IntroScreen intro(window);
	intro.run();

	Menu menu(window);
	menu.setSelectedItem(0);
	menu.addItem(_("New game"));
	menu.addItem(_("Dossiers"));
	menu.addItem(_("Hall of fame"));
	menu.addItem(_("Options"));
	menu.addItem(_("Help"));
	menu.addItem(_("Quit"));

	MediaMusic music("resources/sounds/weird_loop.wav");
	if (configurator.isPlayMusic())
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
			quit = (selected == ConfirmationDialog::DIALOG_OK);
			} break;
		}
	}

	delete window;
	}

	services.destroy();

	return EXIT_SUCCESS;
}

