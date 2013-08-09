#ifndef HELPSCREEN_H
#define HELPSCREEN_H

#include <Window.h>
#include <Surface.h>
#include <Font.h>
#include <Text.h>

class HelpScreen {

private:
	Surface *window;
	Surface backgroundSurf;
	Surface *helpIcon;

	Font font;
	Font fontValue;

	Text *screenTitle;

	Text *turnMusic0;
	Text *turnMusic1;
	Text *turnSounds0;
	Text *turnSounds1;

	Text *fullScreen0;
	Text *fullScreen1;

	Text *saveGame0;
	Text *saveGame1;
	Text *loadGame0;
	Text *loadGame1;

	Text *quit0;
	Text *quit1;

public:
	HelpScreen(Window *window_);
	~HelpScreen();

	void show();
};

#endif

