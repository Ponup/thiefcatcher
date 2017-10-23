#pragma once

#include <SensitiveAreas.h>
#include <Surface.h>
#include <Font.h>
#include <Window.h>

#include "entities/PlayerCase.h"
#include "entities/Place.h"
#include "ui/Clock.h"
#include "ui/widgets/SquareButton.h"

#include <Texture.h>
using Kangaroo::Texture;

#include <Renderer.h>
using Kangaroo::Renderer;

#include <MouseCursor.h>
using Kangaroo::MouseCursor;

enum class GameState {
    Playing,
    LostTimeout,
    LostEscaped,
    Won,
    Abort
};

class Game {
    Window *window;
    Renderer renderer;
    Texture backgroundTexture;

    Font timeFont;
    Point dateTimePosition;

    SquareButton *buttons[4];

    PlayerCase *playerCase;
    Clue* clue;
    Place place;

    GameState state;

    Clock *clock;

    MouseCursor normalCursor, handCursor;

    void drawScene();

    void optionTravel();
    void optionPlaces();
    void optionProfile();

    int calculateHours(Country &from, Country &to);
public:

    static const int Width = 800;
    static const int Height = 600;

    int currentOption;

    Game(Window *window, PlayerCase *playerCase);
    ~Game();

    void enterOption();
    void drawPlacesArea();
    Window *getWindow();
    void quitGame();

    GameState getGameState() const;

    void drawTimeArea();
    void increaseTime(int hours);

    bool isPlaying() const;
    void update();
};
