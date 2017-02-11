#include "CountryDrawing.h"

#include <FontManager.h>
#include <Text.h>
#include <TextUtils.h>
#include <FileUtils.h>
#include <Surface.h>

using Kangaroo::TextUtils;

void drawCountry(Renderer* canvas, const Country &country, bool drawDescription) {
	/** Title area **/
	Font fontCountryName("resources/fonts/FreeSansBold.ttf", 30);
	fontCountryName.setColor(Color(240, 255, 255)); // #F0FFFF

	Text name(country.getName(), &fontCountryName);
	canvas->drawText(&name, Point(358, 105));

	/* Photo area */
	string photoPath = "data/countries/" + country.getIsoCode() + "/postal.png";
	FileUtils fileUtils;
	if (!fileUtils.fileExists(photoPath.c_str())) {
		photoPath = "data/countries/default-photo.jpg";
	}
	Surface photoSurface(photoPath);
	photoSurface.transform(4, 1, 1);
	Texture photoTexture(canvas->internal, photoSurface.toSDL());
	canvas->drawTexture(&photoTexture, Point(47, 115));

	Texture polaroidSurf(canvas->internal, "resources/images/game/polaroid.png");
	canvas->drawTexture(&polaroidSurf, Point(30, 108));

	string flagPath = "data/countries/" + country.getIsoCode() + "/flag.png";
	Surface flagSurface(flagPath);
	flagSurface.transform(0, .5, 1);
	Texture flagTexture(canvas->internal, flagSurface.toSDL());
	canvas->drawTexture(&flagTexture, Point(300, 110));

	if (drawDescription) {
		Font descFont("resources/fonts/FreeSansBold.ttf", 14);
		descFont.setColor(Color(211, 186, 164)); // #D3BAA4	

		Text description(country.getDescription(), &descFont);
		TextUtils textUtils;
		textUtils.drawLines(canvas, description, Point(358, 150), Dimension(360, 340));
	}
}

