#pragma once

#include "SDL.h"

#include "Point.h"
#include "Texture.h"
#include "Text.h"

using Kangaroo::Texture;

namespace Kangaroo {

    class Renderer {
    public:
        int width, height;

        SDL_Renderer* internal;

        Renderer(SDL_Renderer* renderer);
        Renderer(const Renderer& renderer) {
            width = renderer.width;
            height = renderer.height;
            internal = renderer.internal;
        }

        void drawTexture(Texture* texture, const Point& pos = Point::Origin);
        void drawText(Text* text, const Point& pos = Point::Origin);
        void present();
    };
}