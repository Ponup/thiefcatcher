#pragma once

#include <Window.h>

#include <Scene.h>
using Kangaroo::Scene;

class IntroScreen : public Scene {
    Window* screen;

public:
    IntroScreen(Window* screen);
    virtual ~IntroScreen();

    void run();
};
