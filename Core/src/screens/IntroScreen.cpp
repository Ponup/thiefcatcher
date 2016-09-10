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

IntroScreen::IntroScreen(Window* screen) : screen(screen) {
}

IntroScreen::~IntroScreen() {
}

void IntroScreen::run() {
	Font font("resources/fonts/gtw.ttf", 75);
	font.setColor(Color(255, 220, 220));
	font.setStyle(FontStyle::BLENDED);

	Text textLine(_("Thief Catcher"));
	textLine.setFont(&font);

	MediaSound sound("resources/sounds/gunshot.wav");
	sound.play();

	Texture magnifierTexture(screen->renderer, "resources/images/magn_glass.png");
	Texture backgroundTexture(screen->renderer, "resources/images/empty_background.jpg");
	Texture bulletTexture(screen->renderer, "resources/images/bullet.png");

	Point textPos(400 - (textLine.getDimension().w >> 1), 200);
	Point glassPos(textPos.x + textLine.getDimension().w - 40, 200);

	int bulletX = 0;
	float alpha = SDL_ALPHA_TRANSPARENT;
	int radius = 200;
	float angle = 0;

	FrameRegulator fr(150);
	fr.setUp();

	SDL_Event e;

	Renderer renderer(screen->renderer);

	bool quit = false;
	while (!quit) {
		Point position(cos(angle) * radius, sin(angle) * radius);
		textLine.setAlpha(alpha);

		renderer.drawTexture(&backgroundTexture);
		renderer.drawText(&textLine, textPos);
		renderer.drawTexture(&bulletTexture, Point(bulletX, 230));
		renderer.drawTexture(&magnifierTexture, glassPos + position);
		renderer.present();
		fr.regulate();

		bulletX += 18;

		if (alpha < 255) alpha += 3;

		radius -= 0.25;
		angle += 0.05;

		while (SDL_PollEvent(&e))
			quit = (e.type == SDL_QUIT || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_KEYDOWN);
	}
}

