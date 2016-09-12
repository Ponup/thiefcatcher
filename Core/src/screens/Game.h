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
#include <Renderer.h>

using Kangaroo::Texture;
using Kangaroo::Renderer;

enum class GameState {
    Playing,
    LostTimeout,
    LostEscaped,
    Won,
    Abort
};

class Game {

	SensitiveAreas sensAreas;

    Window *window;
	Renderer renderer;
	Texture backgroundTexture;
	
    Font timeFont;
    Point dateTimePosition;

    SDL_Surface *fontSurface;

    SDL_Surface *optionBackup;
    SDL_Rect lastRect;

    SquareButton *buttons[4];

    PlayerCase *playerCase;
	Clue* clue;
	Place place;

    GameState state;

    Clock *clock;

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
