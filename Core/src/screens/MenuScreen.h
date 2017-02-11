#pragma once

#include "Window.h"
#include "utilities/Configurator.h"
#include "ui/widgets/Menu.h"

class MenuScreen {

	Window *window;
	const Configurator *configurator;
	Menu menu;

public:
	MenuScreen(Window *window, const Configurator *configurator);

	void show();
};
