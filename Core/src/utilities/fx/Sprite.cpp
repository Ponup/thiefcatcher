#include "Sprite.h"

Sprite::Sprite(const char *fileName, const int numFrames_, const Dimension &frameDim_, Renderer *renderer)
        : numFrames(numFrames_), frameDim(frameDim_) {
    currentFrame = 0;
    position = Point::Origin;

    frames = new Texture *[numFrames];

    for (int i = 0; i <= numFrames; i++) {
        char path[100] = {};
        sprintf(path, fileName, i);
        frames[i] = new Texture(renderer->internal, path);
    }
}

Sprite::~Sprite() {
    delete *frames;
}

void Sprite::setPosition(const Point &position_) {
    position = position_;
}

void Sprite::clipRenderer(Renderer *renderer) {
    SDL_Rect rect = {position.x, position.y, frameDim.w, frameDim.h};
    SDL_RenderSetClipRect(renderer->internal, &rect);
}

void Sprite::unclipRenderer(Renderer *renderer) {
    SDL_RenderSetClipRect(renderer->internal, nullptr);
}

void Sprite::draw(Renderer *screen) {
    screen->drawTexture(frames[currentFrame], position);
    currentFrame++;
    if (currentFrame > numFrames) currentFrame = 0;
}

