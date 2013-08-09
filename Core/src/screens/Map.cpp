#include "Map.h"

#include <FrameRegulator.h>
#include <SurfaceUtil.h>
#include <System.h>
#include <FontManager.h>

#include <Text.h>

#include "Primitives.h"
#include "MathUtil.h"
#include "MediaManager.h"
#include "MediaMusic.h"
#include "MediaSound.h"

#include "ui/Transitions.h"

#include "utilities/Translator.h"

Map::Map(Surface *window_, Country *from_, Country *to_) : selected(0), quit(false) {
	window = window_;
	
	from = from_;
	to = to_;

	map.load("resources/images/map/bg.png");

	airplane.load("resources/images/map/airplane.png", true);
	airplaneDim = airplane.getDimension();
	airplaneDim.setWidth(airplaneDim.getWidth()+5);
	airplaneDim.setHeight(airplaneDim.getHeight()+5);

	font.load("resources/fonts/FreeSansBold.ttf", 15);
	font.setColor(Color(0x8e, 0x60, 0x3e));

	target.load("resources/images/map/flight_target.gif");
	target_over.load("resources/images/map/flight_target_over.gif");

	updateScreen(false);
	//Transitions::slideTB(window, window->getArea());

	while (!quit) {
		captureEvents();
		updateScreen(true);
		System::delay(30);
	}
}

Map::~Map() {
}

void Map::updateScreen(bool update) {
	window->drawSurface(&map, Point(0, 0));

	font.setColor(Color(0x8e, 0x60, 0x3e));

	char temp[200];
	memset(temp, '\0', 200);
	sprintf(temp, _("You are in %s."), from->getName());

	Text text1(temp, &font);
	text1.draw(Point(40, 510), window);

	Text text(_("Choose your destiny:"), &font);
	text.draw(Point(40, 530), window);

	for (int i = 0; i < 3; i++) {
		Point too = to[i].getCoord() - Point(10, 10);
		window->drawSurface(&target, too);
		//Primitives::drawLine(window, from->getCoord() - Point(10, 10), to[i].getCoord(), Color( 0xff, 0xff, 0xff));
		Point position = too;
		sensAreas.addArea(Area(position, Dimension(20, 20)));
		points[i] = position;
	}

	window->drawSurface(&airplane, from->getCoord() - Point(10, 10));

	Color colorNormal(0, 0, 0);
	Color colorHighlight(0x8e, 0x60, 0x3e);

	unsigned int lineHeight = font.getLineSkip();

	unsigned char posx = 230;
	unsigned int posy = 500;

	Surface tickSurf("resources/images/game/tick.png");

	for (int i = 0; i < 3; i++) {
		Point countryNamePosition(posx, posy);

		if (i == selected) {
			window->drawSurface(&tickSurf, Point(210, posy));
			font.setColor(colorNormal);
			window->drawSurface(&target_over, points[i]);
		} else {
			font.setColor(colorHighlight);
			window->drawSurface(&target, points[i]);
		}

		Text text(to[i].getName(), &font);
		text.draw(countryNamePosition, window);

		posy += lineHeight;
	}

	if (update)
		window->flip();
}

void Map::gotoTarget() {
	quit = true;

	//MediaSound sound("resources/sounds/airplane.wav");

	Surface *areaAirplane = window->getArea(from->getCoord() - Point(10, 10), airplaneDim);
	window->drawSurface(areaAirplane, from->getCoord() - Point(10, 10));
	delete areaAirplane;

	Point pa = from->getCoord() - Point(10, 10);
	Country country = to[selected];
	Point pb = country.getCoord() - Point(10, 10);
	vector<Point> path = MathUtil::calculatePath(pa, pb);
	//	sound.play();

	FrameRegulator fr(25);
	fr.setUp();

	for (unsigned int i = 0; i < path.size(); i++) {
		Point point = from->getCoord() + path.at(i) - Point(10, 10);
		Surface *oldArea = window->getArea(point, airplaneDim);

		window->drawSurface(&airplane, point);
		window->updateArea(point, airplaneDim);
		window->drawSurface(oldArea, point);

		delete oldArea;
		fr.regulate();
	}
}

char Map::getSelection() {
	return selected;
}

void Map::onKeyDown(SDL_KeyboardEvent key) {
	switch (key.keysym.sym) {
	case SDLK_ESCAPE:
		cancelScene();
		break;
	case SDLK_RETURN:
		gotoTarget();
		break;
	case SDLK_UP:
		selected--;
		if (selected == -1)
			selected = 2;
		break;
	case SDLK_DOWN:
		selected++;
		if (selected > 2)
			selected = 0;
		break;
	default:
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
			gotoTarget();
		}
		break;
	}
}

void Map::onMouseButtonUp(SDL_MouseButtonEvent e) {

}

void Map::onMouseMotion(SDL_MouseMotionEvent motion) {
	int resolved = sensAreas.resolve(motion.x, motion.y);
	if (resolved != -1) {
		selected = resolved;
	}
}

void Map::cancelScene() {
	selected = -1;
	quit = true;
}
