#include "Window.h"

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

const int Window::FLAGS_WINDOW = SDL_WINDOW_SHOWN;
const int Window::FLAGS_FULLSCREEN = SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN;

SDL_Renderer* Window::renderer = nullptr;
SDL_Texture* Window::texture = nullptr;

Window::Window(const string& title, const Dimension &dimension) {
    *this = Window(title, dimension, nullptr, false);
}

Window::Window(const string& title_, const Dimension &dimension, const string& iconPath_, bool fullScreen_) :
title(title_), iconPath(iconPath_), dimension(dimension), fullScreen(fullScreen_) {

    defineSurface();
}

Window::~Window() {
    SDL_DestroyWindow(window);
}

void Window::toggleFullScreen() {
    fullScreen = !fullScreen;
    SDL_SetWindowFullscreen(window, fullScreen ? SDL_WINDOW_FULLSCREEN : 0);
}

void Window::defineSurface() {
    int flags = (fullScreen ? Window::FLAGS_FULLSCREEN : Window::FLAGS_WINDOW);

    window = SDL_CreateWindow(title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            dimension.w,
            dimension.h,
            flags);

    if (!iconPath.empty()) {
        SDL_Surface *icon = IMG_Load(iconPath.c_str());
        if (icon != nullptr) {
            SDL_SetWindowIcon(window, icon);
            SDL_FreeSurface(icon);
        }
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
}

Dimension Window::getDimension() const {
    return dimension;
}

SDL_Window* Window::toSDL() {
    return window;
}

SDL_Surface* Window::getSurface(void) {
    return SDL_GetWindowSurface(window);
}
