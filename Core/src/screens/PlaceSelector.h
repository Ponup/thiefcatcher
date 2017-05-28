#pragma once

#include <SDL2_gfxPrimitives.h>

#include <Surface.h>
#include <Window.h>
#include <SurfaceUtil.h>

#include <Font.h>
#include <FontManager.h>
#include <EventHandler.h>

#include <Text.h>

#include <SensitiveAreas.h>

#include "entities/Place.h"
#include "entities/PlacesManager.h"

#include <Renderer.h>

using Kangaroo::Renderer;

class PlaceSelector : public EventHandler {
    SensitiveAreas sensAreas;

    bool quit;

    Place places[3];

    Renderer* renderer;

    Window *screen;

    Point dialogPosition;
    Dimension dialogDimension;

    Texture *images[3];
    SDL_Rect areas[3];

    int selectedIndex;
    int returnCode;

    void drawIcons();
    void draw();

public:
    PlaceSelector(Renderer* renderer, Surface* canvas, vector<Place> randomPlaces);
    ~PlaceSelector();

    void onQuit(SDL_QuitEvent event) {

    }
    void onMouseMotion(SDL_MouseMotionEvent event);
    void onMouseButtonDown(SDL_MouseButtonEvent event);

    void onMouseButtonUp(SDL_MouseButtonEvent event) {

    }
    void onKeyDown(SDL_KeyboardEvent event);

    void onKeyUp(SDL_KeyboardEvent event) {

    }

    int showAndReturn();
};
