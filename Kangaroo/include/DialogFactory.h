#pragma once

#include <string>
using std::string;

#include "Window.h"

class DialogFactory {

public:
	static int showConfirmationDialog(Window *screen, const char *message);
	static void showInformationDialog(Window *screen, const char *message);
};

