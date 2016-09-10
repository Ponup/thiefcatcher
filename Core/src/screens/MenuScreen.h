#pragma once

#include "Window.h"
#include "utilities/Configurator.h"

class MenuScreen
{
	private:
		Window *window;
		const Configurator *configurator;

	public:
		MenuScreen( Window *window_, const Configurator *configurator_ ) : window( window_ ), configurator( configurator_ ) {};
		void show();
};
