#ifndef INTROSCREEN_H_
#define INTROSCREEN_H_

#include <Window.h>

class IntroScreen {

private:
	Window* screen;
	
public:
	IntroScreen(Window* screen);
	virtual ~IntroScreen();
	
	void run();
};

#endif

