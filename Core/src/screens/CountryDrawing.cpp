#include "CountryDrawing.h"

#include <SDL2/SDL.h>
#include <FontManager.h>
#include <Text.h>

void showCountry(Surface *canvas, const Country &country) {
	/** Title area **/
	Font fontCountryName("resources/fonts/FreeSansBold.ttf", 30);
	fontCountryName.setColor(Color(240, 255, 255)); // #F0FFFF

	Text name(country.getName(), &fontCountryName);
	name.draw(Point(358, 105), canvas);
	
	/* Photo area */
	Surface *countryPhoto = country.getPhoto();
	if( NULL != countryPhoto ) {
		Surface *countryPhotoPart = countryPhoto->getArea( Point::Origin, Dimension(278, 298) );
		delete countryPhoto;
		countryPhotoPart->transform( 5, .75, 1 );
//		canvas->drawSurface(countryPhotoPart, Point(30, 108));
		delete countryPhotoPart;
		
	}

	Surface polaroidSurf("resources/images/game/polaroid.png", false);
	canvas->drawSurface(&polaroidSurf, Point(30, 108));
	
	Surface *flag = country.getFlag();
	flag->transform( 0, .5, 1 );
	canvas->drawSurface(flag, Point(300, 110));
	delete flag;

	/* Description area */
	Font descFont("resources/fonts/FreeSansBold.ttf", 14);
	descFont.setColor(Color(211, 186, 164)); // #D3BAA4	
	Surface *descSurface = canvas->getArea(Area(Point(358, 140), Dimension(396, 255)));
	Text description(country.getDescription(), &descFont);
	description.drawLines(Point(3, 3), Dimension(270, 340), descSurface);
	canvas->drawSurface(descSurface, Point(358, 140));
	delete descSurface;
}

