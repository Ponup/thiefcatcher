#include "TextUtils.h"

#include "StringUtil.h"

#include <vector>
#include <exception>

using std::vector;
using std::runtime_error;

void TextUtils::drawLines(Renderer* renderer, const Text& text, const Point& position, const Dimension& containerDimension) const {
    Font* font = text.getFont();
    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font->toSDL(), text.getText().c_str(), font->getColor(), containerDimension.w);
    Texture texture(renderer->internal, surface);
    renderer->drawTexture(&texture, position);
    SDL_FreeSurface(surface);
}