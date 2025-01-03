#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <csignal>

#include <Services.h>

#include <CoreService.h>
#include <MixerService.h>
#include <FontService.h>
#include <Database.h>
using Kangaroo::Database;

#include "entities/PlayersManager.h"

#include "utilities/Updater.h"
#include "utilities/Translator.h"

#include "components/ConfirmationDialog.h"

#include "screens/IntroScreen.h"
#include "screens/MenuScreen.h"

#include "utilities/Configurator.h"

#include <optional>
using std::optional;

#include <filesystem>
namespace fs = std::filesystem;

#include "Version.hpp"

void onInterrupt(int code) {
    cout << "Game interrupted by the user (code: " << code << "). Exiting." << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

    signal(SIGINT, onInterrupt);

    optional<float> newVersionAvailable = Updater::fetchNewVersionAvailable(GAME_VERSION);
    if(newVersionAvailable.has_value()) {
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
    } catch (const std::runtime_error &error) {
        cerr << "An error has occurred: " << error.what() << endl;
        return EXIT_FAILURE;
    }

    Translator::init(configurator.getLanguage());

    Window window(_("Thief Catcher"), Dimension{800, 600}, "resources/logo/thief_256.png", configurator.isFullScreen());

    try {
        const string dbPath{"data/game.db"};
        if(!fs::exists("data/game.db")) {
            cout << "Initializing game database..." << endl;
            fs::copy("data/default-game.db", dbPath);
        }
        Database::getInstance().init(dbPath);
    } catch (const std::runtime_error &error) {
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
