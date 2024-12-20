#pragma once

#include <SDL.h>

class EventHandler {
    SDL_Event event;

public:
    void captureEvents();

protected:
    virtual void onQuit(SDL_QuitEvent);
    virtual void onMouseMotion(SDL_MouseMotionEvent);
    virtual void onMouseButtonDown(SDL_MouseButtonEvent);
    virtual void onMouseButtonUp(SDL_MouseButtonEvent);
    virtual void onKeyDown(SDL_KeyboardEvent);
    virtual void onKeyUp(SDL_KeyboardEvent);
};
