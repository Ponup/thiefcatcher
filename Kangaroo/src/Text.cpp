#include "Text.h"

#include <SDL.h>

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
    if (TTF_SizeText(font->toSDL(), text.c_str(), &width, &height)) {
        throw runtime_error(TTF_GetError());
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
                    = TTF_RenderUTF8_Blended(font->toSDL(), text.c_str(), color);
            break;
        case FontStyle::SOLID:
            fontSurface = TTF_RenderUTF8_Solid(font->toSDL(), text.c_str(), color);
            break;
        case FontStyle::SHADED:
        default:
        {
            SDL_Color bgColor = {0, 0, 0};
            fontSurface = TTF_RenderUTF8_Shaded(font->toSDL(), text.c_str(), color,
                    bgColor);
        }
            break;
    }
    SDL_SetSurfaceAlphaMod(fontSurface, alpha);

    return fontSurface;
}

