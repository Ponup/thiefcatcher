#include "PlaceSelector.h"

PlaceSelector::PlaceSelector(Surface *screen, int *placesPrimaryKeys) {
	this->screen = screen;

	dialogPosition = Point(415, 466);
	dialogDimension = Dimension(348, 130);

	dialogBackup = screen->getArea(dialogPosition, dialogDimension);

	surface = new Surface("resources/images/places/dialog.png");
	screen->drawSurface(surface, Point(415, 466));
	screen->flip();

	quit = false;

	places[0] = PlacesManager::findByPrimaryKey(placesPrimaryKeys[0]);
	places[1] = PlacesManager::findByPrimaryKey(placesPrimaryKeys[1]);
	places[2] = PlacesManager::findByPrimaryKey(placesPrimaryKeys[2]);

	images[0] = places[0].getSurface();
	images[1] = places[1].getSurface();
	images[2] = places[2].getSurface();

	areas[0].y = areas[1].y = areas[2].y = dialogPosition.y + 30;
	areas[0].h = areas[1].h = areas[2].h = areas[0].y + 80;

	areas[0].x = dialogPosition.x + 40;
	areas[0].w = areas[0].x + 80;
	areas[1].x = areas[0].w + 20;
	areas[1].w = areas[1].x + 80;
	areas[2].x = areas[1].w + 20;
	areas[2].w = areas[2].x + 80;

	sensAreas.addArea(Area(areas[0].x, areas[0].y, 70, 90));
	sensAreas.addArea(Area(areas[1].x, areas[1].y, 70, 90));
	sensAreas.addArea(Area(areas[2].x, areas[2].y, 70, 90));

	selectedIndex = 0;
	returnCode = -1;
}

PlaceSelector::~PlaceSelector() {
	delete dialogBackup;

	delete images[0];
	delete images[1];
	delete images[2];

	delete surface;
}

void PlaceSelector::update() {
	//screen->drawSurface(dialogBackup, dialogPosition);
	screen->drawSurface(surface, Point(415, 466));

	for (int i = 0; i < 3; i++) {
		Point point(areas[i].x, areas[i].y);
		screen->drawSurface(images[i], point);
		if (selectedIndex == i) {
			aacircleRGBA(screen->toSDL(), point.x + 40, point.y + 40, 40, 0xff, 0xfc, 0x7b, 255);
			aacircleRGBA(screen->toSDL(), point.x + 40, point.y + 40, 39, 0xff, 0xfc, 0x7b, 255);
		}
	}

	Font *font = FontManager::getFont("FreeSansBold", 14);
	Text text(places[selectedIndex].getName(), font);
	text.draw(Point((dialogDimension.w >> 1) - (text.getDimension().w >> 1), 110), screen);

	screen->updateArea(dialogPosition, dialogDimension);
}

int PlaceSelector::showAndReturn() {
	update();

	while (!quit) {
		captureEvents();
	}

	screen->updateArea(dialogPosition, dialogDimension);

	return returnCode;
}

void PlaceSelector::onKeyDown(SDL_KeyboardEvent event) {
	switch (event.keysym.sym) {
	case SDLK_ESCAPE:
		returnCode = -1;
		quit = true;
		break;
	case SDLK_RETURN:
		returnCode = selectedIndex;
		quit = true;
		break;
	case SDLK_LEFT:
		if (selectedIndex == 0)
			selectedIndex = 2;
		else
			selectedIndex--;
		update();
		break;
	case SDLK_RIGHT:
		if (selectedIndex == 2)
			selectedIndex = 0;
		else
			selectedIndex++;
		update();
		break;
	default:
		break;
	}
}

void PlaceSelector::onMouseMotion(SDL_MouseMotionEvent motion) {
	int resolved = sensAreas.resolve(motion.x, motion.y);
	if (resolved != -1) {
		selectedIndex = resolved;
		update();
	}
}

void PlaceSelector::onMouseButtonDown(SDL_MouseButtonEvent event) {
	if (event.button == SDL_BUTTON_RIGHT) {
		returnCode = -1;
		quit = true;
	} else {
		int resolved = sensAreas.resolve(event.x, event.y);
		if (resolved != -1 && event.button == SDL_BUTTON_LEFT) {
			returnCode = selectedIndex = resolved;
			quit = true;
		}
	}
}

