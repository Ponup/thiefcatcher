#include "IntroScreen.h"

#include <FrameRegulator.h>
#include <FontManager.h>
#include <Font.h>
#include <Text.h>
#include <MediaSound.h>

#include <math.h>

#include <Texture.h>
using Kangaroo::Texture;

#include <Renderer.h>
using Kangaroo::Renderer;

#include "utilities/Translator.h"

#include <GameObject.h>
using Kangaroo::GameObject;

class Magnifier : public GameObject {
    Texture texture;
    int radius = 200;
    float angle = 0;

public:

    Magnifier(Renderer& renderer) :
    GameObject(renderer),
    texture(renderer.internal, "resources/images/magn_glass.png") {
    }

    void update(double time) override {
        (void)time;
        radius -= 0.25;
        angle += 0.05;

    }

    void render() override {
        Point glassPos(600, 200);
        Point position(cos(angle) * radius, sin(angle) * radius);
        renderer.drawTexture(&texture, glassPos + position);
    }

};

class Bullet : public GameObject {
    int bulletX = 0;
    Texture texture;

public:

    Bullet(Renderer& renderer) :
    GameObject(renderer),
    texture(renderer.internal, "resources/images/bullet.png") {
    }

    void update(double time) override {
        (void)time;
        bulletX += 18;
    }

    void render() override {
        renderer.drawTexture(&texture, Point(bulletX, 230));
    }

};

IntroScreen::IntroScreen(Window* screen) : screen(screen) {
}

IntroScreen::~IntroScreen() {
}

void IntroScreen::run() {
    Font font("resources/fonts/gtw.ttf", 75);
    font.setColor(Color(255, 220, 220));
    font.setStyle(FontStyle::BLENDED);

    Text gameNameText(_("Thief Catcher"));
    gameNameText.setFont(&font);

    MediaSound sound("resources/sounds/gunshot.wav");
    sound.play();

    Texture backgroundTexture(screen->renderer, "resources/images/empty_background.jpg");

    Point textPos(400 - (gameNameText.getDimension().w >> 1), 200);

    float alpha = SDL_ALPHA_TRANSPARENT;

    FrameRegulator fr(150);
    fr.setUp();

    SDL_Event e;

    Renderer renderer(screen->renderer);

    Magnifier magnifier(renderer);
    Bullet bullet(renderer);
    gameObjects.push_back(&magnifier);
    gameObjects.push_back(&bullet);

    init();

    bool quit = false;
    while (!quit) {
        gameNameText.setAlpha(alpha);

        updateObjects();
        renderer.drawTexture(&backgroundTexture);
        renderer.drawText(&gameNameText, textPos);
        renderObjects(renderer);
        renderer.present();
        fr.regulate();

        if (alpha < 255) alpha += 3;

        while (SDL_PollEvent(&e))
            quit = (e.type == SDL_QUIT || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_KEYDOWN);
    }
}

