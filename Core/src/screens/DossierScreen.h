#pragma once

#include <vector>
using std::vector;

#include <EventHandler.h>
#include <Window.h>
#include <SensitiveAreas.h>
#include <Font.h>
#include <Surface.h>

#include <Renderer.h>
using Kangaroo::Renderer;

#include <Texture.h>
using Kangaroo::Texture;

#include "entities/Criminal.h"

#include <MouseCursor.h>
using Kangaroo::MouseCursor;

#include <Scene.h>
using Kangaroo::Scene;

class DossierScreen : public Kangaroo::Scene {
    Window *window;

    vector<Criminal> criminals;

    unsigned char index;
    bool quit;

    SensitiveAreas sensAreas;

    Font fontName;
    Font font;

    Texture backgroundTexture;

    MouseCursor normalCursor, handCursor;

    struct CriminalTrait {
        string label;
        string value;
    };

    void renderStaticElements(Renderer& renderer);

public:
    DossierScreen(Window *window);
    virtual ~DossierScreen();

    void show();

    void onMouseMotion(SDL_MouseMotionEvent);
    void onMouseButtonDown(SDL_MouseButtonEvent);
    void onKeyDown(SDL_KeyboardEvent);

};
