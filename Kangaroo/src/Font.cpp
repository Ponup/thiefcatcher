#include "Font.h"

#include <stdexcept>

using std::const_pointer_cast;

Font::Font() {
}

Font::Font(const char *fontPath, unsigned int size) :
path(fontPath),
size(size) {
    load(fontPath, size);
}

void Font::load(const char *fontPath, unsigned int size) {
    internal = shared_ptr<TTF_Font>(TTF_OpenFont(fontPath, size), [](TTF_Font * font) {
        if (font)
            TTF_CloseFont(font);
    });

    if (!internal) {
        throw std::runtime_error(TTF_GetError());
    }
    style = FontStyle::BLENDED;
}

Font::Font(const Font &font) {
    load(font.getPath(), font.getSize());

    this->style = font.getStyle();
    this->color = font.getColor();
}

Font::~Font() {
}

const char *Font::getPath() const {
    return path;
}

int Font::getSize() const {
    return size;
}

void Font::setStyle(FontStyle style) {
    this->style = style;
}

FontStyle Font::getStyle() const {
    return style;
}

void Font::setColor(const Color &color) {
    this->color = color;
}

Color Font::getColor() const {
    return color;
}

unsigned int Font::getLineSkip() const {
    TTF_Font* font = internal.get();
    return TTF_FontLineSkip(font);
}

TTF_Font *Font::toSDL() {
    return internal.get();
}
