#include "Map.h"

#include "MathUtil.h"
#include "MediaSound.h"
#include "Text.h"
#include "utilities/Translator.h"
#include "entities/CountriesManager.h"

Point latlong2point(pair<double, double> latlong)
{
	// y = ((-1 * lat) + 90) * (MAP_HEIGHT / 180);
	// x = ( lon + 180) * (MAP_WIDTH / 360);
	Point point;
	point.y = (int)(((-1 * latlong.first) + 90) * 2.6);
	point.x = (int)((latlong.second + 180) * (720 / 360));
	return point;
}

Map::Map(Renderer* renderer, Country *sourceCountry_, Country *targetCountry_) :
	renderer(renderer),
	selected(0), quit(false), updatePending(true),
	sourceCountry(sourceCountry_), targetCountry(targetCountry_),
	bulletSurface(renderer->internal, "resources/images/map/flight_target.gif"),
	bulletOverSurface(renderer->internal, "resources/images/map/flight_target_over.gif")
	{

	directedAirplane = nullptr;

	mapOffset = Point(50, 80);
	// This point fixes the position of the bullets on the map.
	offsetFix = Point::Origin;

	bulletRadius = Point(10, 10);

	font.load("resources/fonts/FreeSansBold.ttf", 15);
	font.setColor(Color(0x8e, 0x60, 0x3e));

	addSensibleAreas();

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
	if (directedAirplane != nullptr)
		delete directedAirplane;
}

void Map::drawAllCountries()
{
	vector<Country> countries = CountriesManager::findAll();
	for (unsigned int i = 0; i < countries.size(); i++)
	{
		Text text(countries[i].getIsoCode(), &font);
		renderer->drawText(&text, latlong2point(countries[i].getLatitudeLongitude()) + mapOffset - bulletRadius);
	}
}

void Map::addSensibleAreas()
{
	Dimension bulletDimension(20, 20);

	for (int i = 0; i < 3; i++)
	{
		Point p = latlong2point(targetCountry[i].getLatitudeLongitude());
		points[i] = p + mapOffset - bulletRadius + offsetFix;
		sensAreas.addArea(Area(points[i], bulletDimension));
	}
}

void Map::updateScreen(bool update) {

	createStaticBackground();
	drawAllCountries();

	drawOptions();
	drawDirectedAirplane();

	if (update) {
		renderer->present();
	}

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
		renderer->drawText(&text, countryNamePosition);

		posy += lineHeight;
	}
}

void Map::createStaticBackground()
{
	textureSurface = new Texture(renderer->internal, "resources/images/empty_background.jpg");
	renderer->drawTexture(textureSurface);

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
	double deltay = latlong2point(sourceCountry->getLatitudeLongitude()).y - latlong2point(targetCountry[selected].getLatitudeLongitude()).y;
	double deltax = latlong2point(sourceCountry->getLatitudeLongitude()).x - latlong2point(targetCountry[selected].getLatitudeLongitude()).x;
	double angle = MathUtil::radian2degree(atan2(deltax, deltay));
	angle += 45; // because the airplane is rotated already.

	if (directedAirplane != nullptr)
		delete directedAirplane;
	directedAirplane = new Surface("resources/images/map/airplane-30.png", true);
	directedAirplane->transform(angle);
	Texture* airplaneTexture = new Texture(renderer->internal, directedAirplane->toSDL());

	airplanePosition = latlong2point(sourceCountry->getLatitudeLongitude()) - Point(15, 15) + mapOffset - bulletRadius + offsetFix;
	renderer->drawTexture(airplaneTexture, airplanePosition);
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

		airplanePosition =  (*it);//airplanePosition +

		Texture* texture = new Texture(renderer->internal, directedAirplane->toSDL());

		//renderer->drawTexture(texture, airplanePosition);
		updateScreen(true);

		delete texture;

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
		break;
	}
}

void Map::onKeyUp(SDL_KeyboardEvent e) {
}

void Map::onMouseButtonDown(SDL_MouseButtonEvent e) {
	switch (e.button) {
	case SDL_BUTTON_RIGHT:
		cancelScene();
		break;
	case SDL_BUTTON_LEFT:
		int resolved = sensAreas.resolve(e.x, e.y);
		if (resolved != -1) {
			selected = resolved;
			quit = true;
		}
		break;
	}
}

void Map::onMouseButtonUp(SDL_MouseButtonEvent e) {
}

void Map::onMouseMotion(SDL_MouseMotionEvent motion) {
	int resolved = sensAreas.resolve(motion.x, motion.y);
	if (resolved != -1) {
		updatePending = true;
		selected = resolved;
		updateScreen(true);
	}
}

void Map::cancelScene() {
	selected = -1;
	quit = true;
}

