
#include <iostream>
using std::cout;
using std::endl;

#include <signal.h>

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

#include "screens/IntroScreen.h"
#include "screens/MenuScreen.h"

#include "utilities/Configurator.h"

void onInterrupt(int code) {
	printf("Game interrupted by the user (code: %d). Exiting.\n", code);
	exit(1);
}

int main(int argc, char * argv[]) {

	signal(SIGINT, onInterrupt);

	if (false &&Updater::existsNewVersion(GAME_VERSION)) {
		cout << _("A new version of 'Thief Catcher' is available for download!") << endl;
	}

	Kangaroo::Services services;
	services.addService( new CoreService( SDL_INIT_VIDEO ) );
	services.addService(new MixerService(44100,2) );
	services.addService( new FontService() );
	services.init();

	Configurator configurator = Configurator::getInstance();

	try {
		configurator.init();
	} catch ( std::runtime_error &error ) {
		fprintf( stderr, "%s\n", error.what() );
		exit(1);
	}

	Translator::init(configurator.getLanguage());

	Window *window = new Window(_("Thief Catcher"), GAME_WINDOW_W, GAME_WINDOW_H, "resources/logo/thief_256.png", configurator.isFullScreen());

	try {
		Database::init( "data/game.db" );
		Vars::init();
	} catch (std::runtime_error &error) {
		fprintf(stderr, "ERROR: %s\n", error.what());
		exit(1);
	}

	IntroScreen intro( window );
	intro.run();

	MenuScreen menuScreen( window, &configurator );
	menuScreen.show();

	delete window;

	services.destroy();

	return EXIT_SUCCESS;
}

