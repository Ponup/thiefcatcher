#ifndef INTROSCREEN_H_
#define INTROSCREEN_H_

#include <Surface.h>

class IntroScreen {

private:
	Surface* screen;
	
public:
	IntroScreen(Surface* screen);
	virtual ~IntroScreen();
	
	void run();
};

#endif

