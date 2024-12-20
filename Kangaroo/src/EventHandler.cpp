#include "EventHandler.h"

void EventHandler::captureEvents() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                onQuit(event.quit);
                break;
            case SDL_MOUSEMOTION:
                onMouseMotion(event.motion);
                break;
            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(event.button);
                break;
            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(event.button);
                break;
            case SDL_KEYDOWN:
                onKeyDown(event.key);
                break;
            case SDL_KEYUP:
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

