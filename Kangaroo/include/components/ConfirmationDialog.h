#pragma once

#include <string>
using std::string;

#include "AbstractDialog.h"
#include "Window.h"

class ConfirmationDialog : public AbstractDialog {
    Window *screen;
    string message;

    const SDL_MessageBoxButtonData buttons[2] = {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, DIALOG_YES, "Yes"},
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, DIALOG_NO, "No"},
    };

public:
    ConfirmationDialog(Window *screen, const string& message);
    ~ConfirmationDialog();

    int showGetSelected();
};

