
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <signal.h>

#include <Services.h>

#include <CoreService.h>
#include <MixerService.h>
#include <FontService.h>
#include <MediaMusic.h>
#include <Database.h>
using Kangaroo::Database;

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
	cout << "Game interrupted by the user (code: " << code << "). Exiting." << endl;
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {

	signal(SIGINT, onInterrupt);

	if (true){//Updater::existsNewVersion(GAME_VERSION)) {
		cout << _("A new version of 'Thief Catcher' is available for download!") << endl;
	}

	Kangaroo::Services services;
	services.addService(new CoreService(SDL_INIT_VIDEO));
	services.addService(new MixerService(44100, 2));
	services.addService(new FontService());
	services.init();

	Configurator configurator = Configurator::getInstance();

	try {
		configurator.init();
	}
	catch (const std::runtime_error &error) {
		cerr << "An error has occurred: " << error.what() << endl;
		return EXIT_FAILURE;
	}

	Translator::init(configurator.getLanguage());

	Window window(_("Thief Catcher"), GAME_WINDOW_W, GAME_WINDOW_H, "resources/logo/thief_256.png", configurator.isFullScreen());

	try {
		Database::getInstance().init("data/game.db");
		Vars::init();
	}
	catch (const std::runtime_error &error) {
		cerr << "An error has occurred: " << error.what() << endl;
		return EXIT_FAILURE;
	}

	{
		IntroScreen intro(&window);
		intro.run();

		MenuScreen menuScreen(&window, &configurator);
		menuScreen.show();
	}

	services.destroy();

	return EXIT_SUCCESS;
}
