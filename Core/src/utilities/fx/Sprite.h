#pragma once

#include <Renderer.h>
#include <Texture.h>

using Kangaroo::Renderer;
using Kangaroo::Texture;

class Sprite {
private:
    int currentFrame;

    Texture **frames;
    int numFrames;
    Dimension frameDim;
    Point position;

public:
    Sprite(const char *fileName, const int numFrames,
           const Dimension &frameDim, Renderer *renderer);
    ~Sprite();

    void setPosition(const Point &position);
    void clipRenderer(Renderer *renderer);
    void unclipRenderer(Renderer *renderer);
    void draw(Renderer *screen);
};
