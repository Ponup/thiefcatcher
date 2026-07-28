#include "Text.h"

#include <SDL3/SDL.h>

#include "StringUtil.h"

#include <stdexcept>
using std::runtime_error;

Text::Text() : alpha(SDL_ALPHA_OPAQUE) {
}

Text::Text(const string& text) : text(text), alpha(SDL_ALPHA_OPAQUE) {
}

Text::Text(const string& text, Font *font) : text(text), font(font), alpha(SDL_ALPHA_OPAQUE) {
}

Text::~Text() {
}

void Text::setText(const string& text) {
    this->text = text;
}

string Text::getText() const {
    return text;
}

void Text::setFont(Font *font) {
    this->font = font;
}

Font *Text::getFont() const {
    return font;
}

Dimension Text::getDimension() const {
    int width, height;
    if (!TTF_GetStringSize(font->toSDL(), text.c_str(), text.length(), &width, &height)) {
        throw runtime_error(SDL_GetError());
    }

    return Dimension(width, height);
}

void Text::setAlpha(Uint8 alpha) {
    this->alpha = alpha;
}

SDL_Surface* Text::toSDL() {
    SDL_Surface *fontSurface = nullptr;
    Color color = font->getColor();
    switch (font->getStyle()) {
        case FontStyle::BLENDED:
            fontSurface
                    = TTF_RenderText_Blended(font->toSDL(), text.c_str(), text.length(), color);
            break;
        case FontStyle::SOLID:
            fontSurface = TTF_RenderText_Solid(font->toSDL(), text.c_str(), text.length(), color);
            break;
        case FontStyle::SHADED:
        default:
        {
            SDL_Color bgColor = {0, 0, 0, 255};
            fontSurface = TTF_RenderText_Shaded(font->toSDL(), text.c_str(), text.length(), color,
                    bgColor);
        }
            break;
    }
    if (fontSurface) {
        SDL_SetSurfaceAlphaMod(fontSurface, alpha);
    }

    return fontSurface;
}

