#include "Window.h"

#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

const int Window::FLAGS_WINDOW = 0;
const int Window::FLAGS_FULLSCREEN = SDL_WINDOW_FULLSCREEN;

SDL_Renderer* Window::renderer = nullptr;
SDL_Texture* Window::texture = nullptr;

Window::Window(const string& title, const Dimension &dimension) {
    *this = Window(title, dimension, "", false);
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
    SDL_SetWindowFullscreen(window, fullScreen);
}

void Window::defineSurface() {
    Uint32 flags = (fullScreen ? FLAGS_FULLSCREEN : FLAGS_WINDOW);

    window = SDL_CreateWindow(title.c_str(),
            dimension.w,
            dimension.h,
            flags);

    if (!iconPath.empty()) {
        SDL_Surface *icon = IMG_Load(iconPath.c_str());
        if (icon != nullptr) {
            SDL_SetWindowIcon(window, icon);
            SDL_DestroySurface(icon);
        }
    }

    renderer = SDL_CreateRenderer(window, nullptr);
}

Dimension Window::getDimension() const {
    return dimension;
}

SDL_Window* Window::toSDL() {
    return window;
}

SDL_Surface* Window::getSurface() {
    return SDL_GetWindowSurface(window);
}
