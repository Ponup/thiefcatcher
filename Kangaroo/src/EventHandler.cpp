#include "EventHandler.h"

void EventHandler::captureEvents() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                onQuit(event.quit);
                break;
            case SDL_EVENT_MOUSE_MOTION:
                onMouseMotion(event.motion);
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                onMouseButtonDown(event.button);
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                onMouseButtonUp(event.button);
                break;
            case SDL_EVENT_KEY_DOWN:
                onKeyDown(event.key);
                break;
            case SDL_EVENT_KEY_UP:
                onKeyUp(event.key);
                break;
            default:
                break;
        }
    }
}

void EventHandler::onQuit(SDL_QuitEvent quit) {
}

void EventHandler::onMouseMotion(SDL_MouseMotionEvent motion) {
}

void EventHandler::onMouseButtonDown(SDL_MouseButtonEvent button) {
}

void EventHandler::onMouseButtonUp(SDL_MouseButtonEvent button) {
}

void EventHandler::onKeyDown(SDL_KeyboardEvent key) {
}

void EventHandler::onKeyUp(SDL_KeyboardEvent key) {
}

