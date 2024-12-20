#pragma once

#include <SDL.h>

class AbstractDialog {
public:

    enum {
        DIALOG_OK = 0,
        DIALOG_CANCEL,
        DIALOG_YES,
        DIALOG_NO
    };

    const SDL_MessageBoxColorScheme defaultColorScheme = {
        {
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            SDL_MessageBoxColor{ 0x94, 0x94, 0x94 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            { 0xff, 0xff, 0xff },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 0x35, 0x22, 0x22 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            { 0xab, 0xab, 0xab },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 0x3c, 0xa7, 0x9d }
        }
    };

    virtual ~AbstractDialog() {
    }
};

