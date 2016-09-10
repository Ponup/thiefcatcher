#pragma once

#include <SensitiveAreas.h>
#include <Surface.h>
#include <Font.h>
#include <Window.h>

#include "entities/PlayerCase.h"
#include "ui/Clock.h"
#include "ui/widgets/SquareButton.h"

enum class GameState {
    Playing,
    LostTimeout,
    LostEscaped,
    Won,
    Abort
};

class Game {
private:
    SensitiveAreas sensAreas;

    Window *window;
    Surface* bgSurfaceCopy;
    Surface bgSurface;

    Font timeFont;
    Surface *timeControllerSurf;
    Surface *timeSurfBackup;
    Point dateTimePosition;

    SDL_Surface *fontSurface;

    SDL_Surface *optionBackup;
    SDL_Rect lastRect;

    Surface *backupSurf;

    SquareButton *buttons[4];

    PlayerCase *playerCase;

    GameState state;

    Clock *clock;

    void optionTravel();
    void optionPlaces();
    void optionProfile();

    int calculateHours(Country &from, Country &to);
public:
    int currentOption;

    Game(Window *window, PlayerCase *playerCase);
    ~Game();

    void enterOption();
    void updateOption();
    Window *getWindow();
    void quitGame();

    GameState getGameState() const;

    void updateTime();
    void increaseTime(int hours);

    bool isPlaying() const;
    void update();
};
