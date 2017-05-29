#include "DossierScreen.h"

#include <sstream>
using std::ostringstream;

#include <string>
using std::string;

#include <Text.h>
#include <FontManager.h>
#include <FrameRegulator.h>

#include "utilities/Translator.h"
#include "entities/CriminalsManager.h"
#include "entities/format/CriminalFormatter.h"

#include <Renderer.h>

using Kangaroo::Renderer;

DossierScreen::DossierScreen(Window *window_) :
window(window_),
backgroundTexture(window_->renderer, 800, 600),
normalCursor(SDL_SYSTEM_CURSOR_ARROW),
handCursor(SDL_SYSTEM_CURSOR_HAND) {
    criminals = CriminalsManager::findAll();

    sensAreas.addArea(Area(Point(28, 511), Dimension(61, 61)));

    index = 0;
    quit = false;

    fontName.load("resources/fonts/FreeSansBold.ttf", 30);
    fontName.setColor(Color(255, 200, 100));

    font.load("resources/fonts/FreeSansBold.ttf", 18);

    Renderer renderer(window_->renderer);

    backgroundTexture.selectAsRenderingTarget(window_->renderer);

    Texture t(window->renderer, "resources/images/dossiers/background.png");
    renderer.drawTexture(&t);

    Font headerFont("resources/fonts/gtw.ttf", 45);
    headerFont.setColor(Color(255, 220, 220));
    Text headerText(_("Thief Catcher"), &headerFont);
    renderer.drawText(&headerText, Point(30, 10));

    backgroundTexture.unselectAsRenderingTarget(window_->renderer);

    updateScreen(false);
}

DossierScreen::~DossierScreen() {
}

void DossierScreen::show() {
    FrameRegulator fr(120);
    fr.setUp();

    while (!quit) {
        captureEvents();
        updateScreen(true);
        fr.regulate();
    }
}

void DossierScreen::updateScreen(bool update) {
    if (!update) {
        return;
    }
    Criminal &criminal = criminals.at(index);

    ostringstream pathStream;
    pathStream << "data/criminals/" << criminal.getID() << ".jpg";

    Renderer renderer(window->renderer);

    renderer.drawTexture(&backgroundTexture);

    Texture avatarTexture(window->renderer, pathStream.str());
    renderer.drawTexture(&avatarTexture, Point(460, 90));

    Text nameText(criminal.getName(), &fontName);
    renderer.drawText(&nameText, Point(140, 140));

    const struct CriminalTrait traits[] = {
        {_("Genre"), CriminalFormatter::formatGenre(criminal)},
        {_("Build"), criminal.getBuild()},
        {_("Hair"), criminal.getHairColor()},
        {_("Feature"), criminal.getFeature()},
        {_("Complexion"), criminal.getComplexion()},
    };
    const size_t numTraits = sizeof (traits) / sizeof (traits[0]);

    int y = 250;
    for (size_t i = 0; i < numTraits; i++) {
        struct CriminalTrait trait = traits[i];

        Text labelText(trait.label, &font);
        font.setColor(Color(0, 0, 0));

        renderer.drawText(&labelText, Point(300 - labelText.getDimension().w, y));

        Text valueText(trait.value, &font);
        font.setColor(Color(200, 160, 60));
        renderer.drawText(&valueText, Point(320, y));

        y += labelText.getDimension().h + (labelText.getDimension().h >> 1);
    }

    renderer.present();
}

void DossierScreen::onQuit(SDL_QuitEvent e) {

}

void DossierScreen::onMouseMotion(SDL_MouseMotionEvent e) {
    if (sensAreas.resolve(e.x, e.y) == -1)
        normalCursor.applyToWindow();
    else
        handCursor.applyToWindow();
}

void DossierScreen::onMouseButtonDown(SDL_MouseButtonEvent e) {
    if (sensAreas.resolve(e.x, e.y) != -1) {
        quit = true;
    }
    if (e.button == SDL_BUTTON_RIGHT) {
        quit = true;
    }
}

void DossierScreen::onMouseButtonUp(SDL_MouseButtonEvent e) {

}

void DossierScreen::onKeyDown(SDL_KeyboardEvent e) {
    switch (e.keysym.sym) {
        case SDLK_RIGHT:
            if (index + 1 < static_cast<int> (criminals.size())) {
                index++;
            }
            break;
        case SDLK_LEFT:
            if (index > 0) {
                index--;
            }
            break;
        case SDLK_ESCAPE:
            quit = true;
            break;
        default:
            break;
    }
}

void DossierScreen::onKeyUp(SDL_KeyboardEvent e) {

}
