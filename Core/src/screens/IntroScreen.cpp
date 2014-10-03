#include "IntroScreen.h"

#include <FrameRegulator.h>
#include <FontManager.h>
#include <Font.h>
#include <Text.h>
#include <MediaSound.h>

#include <math.h>

#include "utilities/Translator.h"

IntroScreen::IntroScreen(Surface *screen_) : screen(screen_) {
}

IntroScreen::~IntroScreen() {
}

void IntroScreen::run() {
	Font font("resources/fonts/gtw.ttf", 75);
	font.setColor(Color(255, 220, 220));
	font.setStyle(BLENDED);

	Text textLine(_("Thief Catcher"));
	textLine.setFont(&font);

	MediaSound sound("resources/sounds/gunshot.wav");
	sound.play();

	Surface glassSurf("resources/images/magn_glass.png", true);
	Surface bgSurf("resources/images/empty_background.jpg");

	Surface bulletSurf("resources/images/bullet.png", true);

	Point textPos( 400 - ( textLine.getDimension().w >> 1 ), 200 ); 
	Point glassPos( textPos.x + textLine.getDimension().w - 40, 200 );

	int bulletX = 0;
	float alpha = SDL_ALPHA_TRANSPARENT;
	int radius = 200;
	float angle = 0;

	FrameRegulator fr(150);
	fr.setUp();

	SDL_Event e;

	bool quit = false;
	while(!quit) {
		Point position(cos(angle) * radius, sin(angle) * radius);
		textLine.setAlpha(alpha);

		screen->drawSurface(&bgSurf, Point(0, 0));		
		textLine.draw( textPos, screen );
		screen->drawSurface(&bulletSurf, Point(bulletX, 230));
		screen->drawSurface(&glassSurf, glassPos + position);

		screen->flip();
		fr.regulate();

		bulletX += 18;

		if(alpha < 255) alpha += 3;

		radius -= 0.25;
		angle += 0.05;

		while(SDL_PollEvent(&e))
			quit = ( e.type == SDL_QUIT || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_KEYDOWN );
	}
}

