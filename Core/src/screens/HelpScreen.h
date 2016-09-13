#pragma once

#include <Renderer.h>
using Kangaroo::Renderer;

class HelpScreen {

	Renderer* renderer;

public:
	HelpScreen(Renderer* renderer);
	~HelpScreen();

	void show();
};
