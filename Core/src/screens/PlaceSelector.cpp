#include "PlaceSelector.h"

PlaceSelector::PlaceSelector(Renderer* renderer, Surface* bgSxurface, vector<Place> randomPlaces) :
	renderer(renderer)
	{

	dialogPosition = Point(415, 466);
	dialogDimension = Dimension(348, 130);

	quit = false;

	places[0] = randomPlaces[0];
	places[1] = randomPlaces[1];
	places[2] = randomPlaces[2];

	images[0] = new Texture(renderer->internal, "resources/images/places/" + places[0].getName() + ".png");
	images[1] = new Texture(renderer->internal, "resources/images/places/" + places[1].getName() + ".png");
	images[2] = new Texture(renderer->internal, "resources/images/places/" + places[2].getName() + ".png");

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

	draw();
}

PlaceSelector::~PlaceSelector() {
	delete images[0];
	delete images[1];
	delete images[2];
}

int PlaceSelector::showAndReturn() {
	draw();

	while (!quit) {
		captureEvents();
	}

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
			draw();
			break;
		case SDLK_RIGHT:
			if (selectedIndex == 2)
				selectedIndex = 0;
			else
				selectedIndex++;
			draw();
			break;
		default:
			break;
	}
}

void PlaceSelector::onMouseMotion(SDL_MouseMotionEvent motion) {
	int resolved = sensAreas.resolve(motion.x, motion.y);
	if (resolved != -1) {
		selectedIndex = resolved;
		draw();
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

void PlaceSelector::drawIcons() {
	if (selectedIndex < 3) {
		Font *font = FontManager::getFont("FreeSansBold", 14);
		font->setColor(Color(0xff, 0xff, 0xff));
		Text text(places[selectedIndex].getName(), font);
		renderer->drawText(&text, dialogPosition + Point((dialogDimension.w >> 1) - (text.getDimension().w >> 1), 110));
	}

	for (int i = 0; i < 3; i++) {
		Point point(areas[i].x, areas[i].y);
		renderer->drawTexture(images[i], point);
	}

	for (int i = 0; i < 3; i++) {
		Point point(areas[i].x, areas[i].y);
		if (selectedIndex == i) {
			aacircleRGBA(renderer->internal, point.x + 40, point.y + 40, 40, 0xff, 0xfc, 0x7b, 255);
			aacircleRGBA(renderer->internal, point.x + 40, point.y + 40, 39, 0xff, 0xfc, 0x7b, 255);
		}
	}
}

void PlaceSelector::draw() {
	Texture balloonTexture(renderer->internal, "resources/images/places/dialog.png");
	renderer->drawTexture(&balloonTexture, Point(415, 466));
	drawIcons();
	renderer->present();
}

