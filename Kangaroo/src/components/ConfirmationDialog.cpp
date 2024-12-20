#include "components/ConfirmationDialog.h"

#include "FontManager.h"
#include "SurfaceUtil.h"

ConfirmationDialog::ConfirmationDialog(Window *screen, const string& message) : screen(screen), message(message) {
}

ConfirmationDialog::~ConfirmationDialog() {
}

int ConfirmationDialog::showGetSelected() {
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        screen->toSDL(), /* .window */
        "Confirmation", /* .title */
        message.c_str(), /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &defaultColorScheme /* .colorScheme */
    };
    
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        return DIALOG_YES;
    }
    
    return buttonid;
}

