#include "CountryDrawing.h"

#include <FontManager.h>
#include <Text.h>
#include <TextUtils.h>
#include <FileUtils.h>
#include <Surface.h>

#include "entities/format/CountryDescriptionGenerator.h"

using Kangaroo::TextUtils;

void drawCountry(Renderer *canvas, const Country &country, bool drawDescription)
{
    /** Title area **/
    Font fontCountryName("resources/fonts/FreeSansBold.ttf", 30);
    fontCountryName.setColor(Color(0xf0, 0xff, 0xff));

    Text name(country.getName(), &fontCountryName);
    canvas->drawText(&name, Point(358, 105));

    /* Photo area */
    string photoPath = "data/countries/" + country.getIsoCode() + "/postal.png";
    FileUtils fileUtils;
    if (!fileUtils.fileExists(photoPath.c_str()))
    {
        photoPath = "data/countries/default-photo.jpg";
    }
    Surface photoSurface(photoPath);
    photoSurface.transform(canvas->internal, 4, 1, 1);
    Texture photoTexture(canvas->internal, photoSurface.toSDL());
    canvas->drawTexture(&photoTexture, Point(47, 115));

    Texture polaroidSurf(canvas->internal, "resources/images/game/polaroid.png");
    canvas->drawTexture(&polaroidSurf, Point(30, 108));

    string flagPath = "data/countries/" + country.getIsoCode() + "/flag.png";
    Surface flagSurface(flagPath);
    flagSurface.transform(canvas->internal, 0, .5, 1);
    Texture flagTexture(canvas->internal, flagSurface.toSDL());
    canvas->drawTexture(&flagTexture, Point(300, 110));

    if (drawDescription)
    {
        Font descFont("resources/fonts/FreeSansBold.ttf", 14);
        descFont.setColor(Color(0xd3, 0xba, 0xa4));

        CountryDescriptionGenerator countryDescriptionGenerator;
        Text description(countryDescriptionGenerator.generateDescription(country), &descFont);
        TextUtils textUtils;
        textUtils.drawLines(canvas, description, Point(358, 150), Dimension(360, 340));
    }
}
