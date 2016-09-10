#pragma once

#include <Window.h>

class IntroScreen {

	Window* screen;

public:
	IntroScreen(Window* screen);
	virtual ~IntroScreen();

	void run();
};
