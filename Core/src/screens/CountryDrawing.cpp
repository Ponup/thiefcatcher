#include "CountryDrawing.h"

#include <SDL.h>
#include <FontManager.h>
#include <Text.h>

void drawCountry(Renderer* canvas, const Country &country) {
	/** Title area **/
	Font fontCountryName("resources/fonts/FreeSansBold.ttf", 30);
	fontCountryName.setColor(Color(240, 255, 255)); // #F0FFFF

	Text name(country.getName(), &fontCountryName);
	canvas->drawText(&name, Point(358, 105));
	
	/* Photo area */
	Surface *countryPhoto = country.getPhoto();
	if( nullptr != countryPhoto ) {
		Surface *countryPhotoPart = countryPhoto->getArea( Point::Origin, Dimension(278, 298) );
		countryPhotoPart->transform(5, .75, 1);
		Texture photoTexture(canvas->internal, countryPhotoPart->toSDL());
		canvas->drawTexture(&photoTexture, Point(30, 108));
		delete countryPhoto;
		delete countryPhotoPart;
		
	}

	Texture polaroidSurf(canvas->internal, "resources/images/game/polaroid.png");
	canvas->drawTexture(&polaroidSurf, Point(30, 108));
	
	string flagPath = "data/countries/" + country.getIsoCode() + "/flag.png";
	Surface flagSurface(flagPath);
	flagSurface.transform(0, .5, 1);
	Texture flagTexture(canvas->internal, flagSurface.toSDL());
	canvas->drawTexture(&flagTexture, Point(300, 110));

	/* Description area */
	Font descFont("resources/fonts/FreeSansBold.ttf", 14);
	descFont.setColor(Color(211, 186, 164)); // #D3BAA4	
	/*
	Surface *descSurface = canvas->getArea(Area(Point(358, 140), Dimension(396, 255)));
	Text description(country.getDescription(), &descFont);
	description.drawLines(Point(3, 3), Dimension(270, 340), descSurface);
	canvas->drawTexture(&descSurface, Point(358, 140));
	delete descSurface;
	*/
}

