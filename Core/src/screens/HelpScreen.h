#ifndef HELPSCREEN_H
#define HELPSCREEN_H

#include <Window.h>

class HelpScreen {

private:
	Window *window;

public:
	HelpScreen( Window *window_ );
	~HelpScreen();

	void show();
};

#endif

