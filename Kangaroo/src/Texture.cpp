#include "Texture.h"

#include <SDL_image.h>

Kangaroo::Texture::Texture(SDL_Renderer* renderer, int width, int height) :
width(width),
height(height) {
    internal = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
}

Kangaroo::Texture::Texture(SDL_Renderer* renderer, const string& path) {
    internal = IMG_LoadTexture(renderer, path.c_str());
    init();
}

Kangaroo::Texture::Texture(SDL_Renderer* renderer, SDL_Surface* surface) {
    internal = SDL_CreateTextureFromSurface(renderer, surface);
    init();
}

Kangaroo::Texture::~Texture() {
    SDL_DestroyTexture(internal);
}

void Kangaroo::Texture::init() {
    if (SDL_QueryTexture(internal, NULL, NULL, &width, &height) != 0) {
        // Log warning
    }
}

SDL_Texture* Kangaroo::Texture::getInternal() {
    return internal;
}

void Kangaroo::Texture::selectAsRenderingTarget(SDL_Renderer* renderer) {
    SDL_SetRenderTarget(renderer, internal);
}

void Kangaroo::Texture::unselectAsRenderingTarget(SDL_Renderer* renderer) {
    SDL_SetRenderTarget(renderer, NULL);
}

int Kangaroo::Texture::getWidth() const {
    return width;
}

int Kangaroo::Texture::getHeight() const {
    return height;
}

int Kangaroo::Texture::setAlphaMod(Uint8 alpha) {
    return SDL_SetTextureAlphaMod(internal, alpha);
}

