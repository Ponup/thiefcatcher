#include "Map.h"

#include "MathUtil.h"
#include "MediaSound.h"
#include "Text.h"
#include "utilities/Translator.h"
#include "entities/CountriesManager.h"

Map::Map(Renderer* renderer, Country *sourceCountry_, Country *targetCountry_) :
	renderer(renderer),
	selected(0), quit(false), updatePending(true),
	sourceCountry(sourceCountry_), targetCountry(targetCountry_),
	backgroundTexture(renderer->internal, "resources/images/empty_background.jpg"),
	bulletSurface(renderer->internal, "resources/images/map/flight_target.gif"),
	bulletOverSurface(renderer->internal, "resources/images/map/flight_target_over.gif"),
	normalCursor(SDL_SYSTEM_CURSOR_ARROW),
	handCursor(SDL_SYSTEM_CURSOR_HAND)
{
	mapOffset = Point(50, 80);
	// This point fixes the position of the bullets on the map.
	offsetFix = Point::Origin;

	bulletRadius = Point(10, 10);

	font.load("resources/fonts/FreeSansBold.ttf", 15);
	font.setColor(Color(0x8e, 0x60, 0x3e));

	addSensibleAreas();

	airplanePosition = sourceCountry->getCoordinates().toScreenCoordinates() - Point(15, 15) + mapOffset - bulletRadius + offsetFix;
	originalAirplanePosition = sourceCountry->getCoordinates().toScreenCoordinates() - Point(15, 15) + mapOffset - bulletRadius + offsetFix;

	updateScreen(true);

	while (!quit) {
		captureEvents();

		if (updatePending) updateScreen(true);

		SDL_Delay(30);
	}

	if (-1 != selected)
		gotoTarget();
}

Map::~Map() {
}

void Map::drawCountriesLabels()
{
	vector<Country> countries = CountriesManager::findAll();
	for (unsigned int i = 0; i < countries.size(); i++)
	{
		Text text(countries[i].getIsoCode(), &font);
		renderer->drawText(&text, countries[i].getCoordinates().toScreenCoordinates() + mapOffset - bulletRadius);
	}
}

void Map::addSensibleAreas()
{
	Dimension bulletDimension(20, 20);

	for (int i = 0; i < 3; i++)
	{
		Point p = targetCountry[i].getCoordinates().toScreenCoordinates();
		points[i] = p + mapOffset - bulletRadius + offsetFix;
		sensAreas.addArea(Area(points[i], bulletDimension));
	}
}

void Map::updateScreen(bool update) {
	(void)update;
	
	drawBackgroundElements();
	drawCountriesLabels();
	drawOptions();
	drawDirectedAirplane();
	renderer->present();

	updatePending = false;
}

void Map::drawOptions()
{
	font.setColor(Color(0x8e, 0x60, 0x3e));

	Color colorNormal(0, 0, 0);
	Color colorHighlight(0x8e, 0x60, 0x3e);

	unsigned int lineHeight = font.getLineSkip();

	unsigned char posx = 230;
	unsigned int posy = 505;

	Texture tickSurf(renderer->internal, "resources/images/game/tick.png");

	for (int i = 0; i < 3; i++) {
		Point countryNamePosition(posx, posy);

		if (i == selected) {
			renderer->drawTexture(&tickSurf, Point(210, posy));
			font.setColor(colorNormal);
			renderer->drawTexture(&bulletOverSurface, points[i]);
		}
		else {
			font.setColor(colorHighlight);
			renderer->drawTexture(&bulletSurface, points[i]);
		}

		Text text(targetCountry[i].getName(), &font);
		Area area;
		area.setPoint(countryNamePosition);
		area.setDimension(text.getDimension());
		sensAreas.addArea(area);
		renderer->drawText(&text, countryNamePosition);

		posy += lineHeight;
	}

	font.setColor(colorHighlight);
}

void Map::drawBackgroundElements()
{
	renderer->drawTexture(&backgroundTexture);

	Texture mapSurface(renderer->internal, "resources/images/map/mercator-map-small.png");
	renderer->drawTexture(&mapSurface, mapOffset);

	Font currentLocationFont("resources/fonts/FreeSansBold.ttf", 30);
	currentLocationFont.setColor(Color(255, 220, 220));

	char temp[200];
	memset(temp, '\0', 200);
	sprintf(temp, _("You are in %s.").c_str(), sourceCountry->getName().c_str());
	Text currentLocationText(temp, &currentLocationFont);
	renderer->drawText(&currentLocationText, Point(50, 20));

	Text text(_("Choose your destination:"), &font);
	renderer->drawText(&text, Point(50, 505));
}

void Map::drawDirectedAirplane()
{
	double deltay = sourceCountry->getCoordinates().toScreenCoordinates().y - targetCountry[selected].getCoordinates().toScreenCoordinates().y;
	double deltax = sourceCountry->getCoordinates().toScreenCoordinates().x - targetCountry[selected].getCoordinates().toScreenCoordinates().x;
	double angle = MathUtil::radian2degree(atan2(deltax, deltay));
	angle += 45; // because the airplane is rotated already.

	Surface directedAirplane("resources/images/map/airplane-30.png", true);
	directedAirplane.transform(angle);
	Texture airplaneTexture(renderer->internal, directedAirplane.toSDL());

	renderer->drawTexture(&airplaneTexture, airplanePosition);
}

void Map::gotoTarget() {
	quit = true;

	Point sourcePoint = airplanePosition;
	Point targetPoint = points[selected] - bulletRadius;
	vector<Point> path = MathUtil::calculatePath(sourcePoint, targetPoint);

	MediaSound sound("resources/sounds/airplane.wav");
	sound.play();

	vector<Point>::iterator it;
	it = path.begin();

	SDL_Event ev;

	bool stopAnimation = false;
	while (!stopAnimation) {
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT || ev.type == SDL_KEYDOWN || ev.type == SDL_MOUSEBUTTONDOWN) {
				stopAnimation = true;
			}
		}

		airplanePosition = originalAirplanePosition + (*it);

		double deltay = sourceCountry->getCoordinates().toScreenCoordinates().y - targetCountry[selected].getCoordinates().toScreenCoordinates().y;
		double deltax = sourceCountry->getCoordinates().toScreenCoordinates().x - targetCountry[selected].getCoordinates().toScreenCoordinates().x;
		double angle = MathUtil::radian2degree(atan2(deltax, deltay));
		angle += 45; // because the airplane is rotated already.

		Surface directedAirplane("resources/images/map/airplane-30.png", true);
		directedAirplane.transform(angle);
		Texture airplaneTexture(renderer->internal, directedAirplane.toSDL());

		updateScreen(true);
		
		it++;

		if (it == path.end()) {
			break; // the outer loop
		}

		SDL_Delay(10);
	}

	SDL_Delay(600);
}

char Map::getSelection() {
	return selected;
}

void Map::onKeyDown(SDL_KeyboardEvent key) {
	updatePending = true;
	switch (key.keysym.sym) {
	case SDLK_ESCAPE:
		cancelScene();
		break;
	case SDLK_RETURN:
		quit = true;
		updateScreen(true);
		break;
	case SDLK_UP:
		selected--;
		if (selected == -1)
			selected = 2;
		updateScreen(true);
		break;
	case SDLK_DOWN:
		selected++;
		if (selected > 2)
			selected = 0;
		updateScreen(true);
		break;
	}
}

void Map::onKeyUp(SDL_KeyboardEvent e) {
	(void)e;
}

void Map::onMouseButtonDown(SDL_MouseButtonEvent e) {
	switch (e.button) {
	case SDL_BUTTON_RIGHT:
		cancelScene();
		break;
	case SDL_BUTTON_LEFT:
		int resolved = sensAreas.resolve(e.x, e.y);
		if (resolved != -1) {
			if(resolved > 2) {
				resolved -= 3;
			}
			selected = resolved;
			quit = true;
		}
		break;
	}
}

void Map::onMouseButtonUp(SDL_MouseButtonEvent e) {
	(void)e;
}

void Map::onMouseMotion(SDL_MouseMotionEvent motion) {
	int resolved = sensAreas.resolve(motion.x, motion.y);
	if (resolved != -1) {
		if(resolved > 2) {
			resolved -= 3;
		}
		handCursor.applyToWindow();
		updatePending = true;
		selected = resolved;
		updateScreen(true);
	}
	else {
		normalCursor.applyToWindow();
	}
}

void Map::cancelScene() {
	selected = -1;
	quit = true;
}

