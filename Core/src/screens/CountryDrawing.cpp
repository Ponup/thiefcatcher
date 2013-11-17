#include "CountryDrawing.h"

#include <SDL.h>
#include <FontManager.h>

#include <SDL_rotozoom.h>

#include <Text.h>

void showCountry(Surface *window, const Country &country) {
	/** Title area **/
	Font fontCountryName("resources/fonts/FreeSansBold.ttf", 30);
	fontCountryName.setColor(Color(240, 255, 255)); // #F0FFFF

	Text name(country.getName(), &fontCountryName);
	name.draw(Point(358, 105), window);
	
	/* Photo area */
	Surface *countryPhoto = country.getPhoto();
	if( NULL != countryPhoto ) {
		Surface *temp = countryPhoto->getArea(Point(0, 0), Dimension(278, 298));
		Surface photo(rotozoomSurface(temp->toSDL(), 5, .75, 1));
		window->drawSurface(&photo, Point(30, 108));
		delete temp;
		
		Surface polaroidSurf("resources/images/game/polaroid.png", false);
		window->drawSurface(&polaroidSurf, Point(30, 108));
	}
	
	Surface *flag = country.getFlag();
	Surface rotatedFlag(rotozoomSurface(flag->toSDL(), 0, 0.5, 1));
	window->drawSurface(&rotatedFlag, Point(300, 110));
	delete flag;

	/* Description area */
	Font descFont("resources/fonts/FreeSansBold.ttf", 14);
	descFont.setColor(Color(211, 186, 164)); // #D3BAA4	
	Surface *descSurface = window->getArea(Area(Point(358, 140), Dimension(396, 255)));
	Text description(country.getDescription(), &descFont);
	description.drawLines(Point(3, 3), Dimension(270, 340), descSurface);
	window->drawSurface(descSurface, Point(358, 140));
	delete descSurface;
}

