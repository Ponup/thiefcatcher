#ifndef HELPSCREEN_H
#define HELPSCREEN_H

#include <Window.h>
#include <Surface.h>

class HelpScreen {

private:
	Surface *window;

public:
	HelpScreen( Window *window_ );
	~HelpScreen();

	void show();
};

#endif

