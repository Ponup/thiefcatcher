#ifndef GAME_H
#define GAME_H

#include <SensitiveAreas.h>
#include <Surface.h>
#include <Font.h>
#include <Window.h>

#include "entities/PlayerCase.h"
#include "ui/Clock.h"

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
		Surface* canvas;
		Surface background;

		Font timeFont;
		Surface *timeControllerSurf;
		Surface *timeSurfBackup;
		Point dateTimePosition;
		
		SDL_Surface *fontSurface;
		
		SDL_Surface *optionBackup;
		SDL_Rect lastRect;
		
		Surface *backupSurf;
		
		Surface *options[4];
		Surface *options_over[4];		
		Point points[4];
		
		string labels[4];
		
		PlayerCase *playerCase;
		
		GameState state;

		Clock *clock;
				
		void optionTravel();
		void optionNotes();
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

		GameState getGameState();

		void updateTime();
		void increaseTime(int hours);

		bool isPlaying();
		void update();
};

#endif
