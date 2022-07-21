#pragma once

#include <EventHandler.h>
#include <Surface.h>
#include <Window.h>
#include <Font.h>
#include <SensitiveAreas.h>

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "entities/PlayerCase.h"

#include <Renderer.h>
#include <Texture.h>

using Kangaroo::Renderer;
using Kangaroo::Texture;

#include <optional>
using std::optional;

class ProfileScreen : public EventHandler {
    Window *screen;
    Renderer* renderer;
    PlayerCase *playerCase;

    Texture backgroundTexture;

    bool quit;

    int option;

    Font fontHeader;
    Font fontOptions;
    Font fontButtons;

    size_t genreIndex;

    size_t hairIndex;
    vector<string> hairsList;

    size_t buildIndex;
    vector<string> builds;

    size_t featureIndex;
    vector<string> featuresList;

    int returnCode;

    SensitiveAreas sensAreas;

    void drawElements();

public:
    ProfileScreen(Renderer* renderer, PlayerCase *playerCase_);
    ~ProfileScreen();

    int run();

    void onQuit(SDL_QuitEvent) override;
    void onMouseMotion(SDL_MouseMotionEvent) override;
    void onMouseButtonDown(SDL_MouseButtonEvent) override;
    void onMouseButtonUp(SDL_MouseButtonEvent) override;
    void onKeyDown(SDL_KeyboardEvent) override;
    void onKeyUp(SDL_KeyboardEvent) override;
};
