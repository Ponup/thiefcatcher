#pragma once

#include <memory>
using std::shared_ptr;
using std::make_shared;

#include <SDL_ttf.h>

#include "Color.h"

enum class FontStyle {
    SOLID = 1,
    SHADED = 2,
    BLENDED = 3
};

class Font {

    enum class Style {
        Solid = 1,
        Shaded,
        Blended
    };

    shared_ptr<TTF_Font> internal;
    FontStyle style;
    Color color;

    const char *path;
    int size;

public:
    Font();
    Font(const char *fontPath, unsigned int size);
    Font(const Font &font);
    ~Font();

    void load(const char *fontPath, unsigned int size);

    int getSize() const;
    const char *getPath() const;

    void setStyle(FontStyle style);
    FontStyle getStyle() const;
    void setColor(const Color &color);
    Color getColor() const;

    unsigned int getLineSkip() const;

    TTF_Font *toSDL();
};

