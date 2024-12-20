#pragma once

#include <SDL.h>

#include <string>
using std::string;

namespace Kangaroo {

    class Texture {
        SDL_Texture* internal;
        int width, height;

        void init();

    public:
        Texture(SDL_Renderer* renderer, int width, int height);
        Texture(SDL_Renderer* renderer, const string& path);
        Texture(SDL_Renderer* renderer, SDL_Surface* surface);
        ~Texture();

        SDL_Texture* getInternal();

        void selectAsRenderingTarget(SDL_Renderer* renderer);
        void unselectAsRenderingTarget(SDL_Renderer* renderer);

        int setAlphaMod(Uint8 alpha);
        int getWidth() const;
        int getHeight() const;
    };
}
