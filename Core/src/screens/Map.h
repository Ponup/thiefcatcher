#pragma once

#include <EventHandler.h>
#include <SensitiveAreas.h>
#include <Surface.h>
#include <Window.h>
#include <Font.h>
#include <Dimension.h>
#include <Point.h>

#include "entities/Country.h"

#include <Renderer.h>
using Kangaroo::Renderer;

#include <Texture.h>
using Kangaroo::Texture;

#include <MouseCursor.h>
using Kangaroo::MouseCursor;

class Map : public EventHandler {

	Renderer* renderer;
	SensitiveAreas sensAreas;
	int selected;
	bool quit;
	bool updatePending;

	Country* sourceCountry;
	Country* targetCountry;

	Texture backgroundTexture;

	Font font;

	Dimension airplaneDim;
	Point airplanePosition, originalAirplanePosition;

	Point mapOffset;
	Point offsetFix;
	Surface map;

	Point bulletRadius;
	Texture bulletSurface;
	Texture bulletOverSurface;

	Point points[3];

	MouseCursor normalCursor, handCursor;

	void addSensibleAreas();
	void drawCountriesLabels();
	void drawBackgroundElements();
	void drawOptions();
	void drawDirectedAirplane();
	void updateScreen(bool update);
	void gotoTarget();

	/**
	 * This method is called when the user presses ESCAPE or RIGHT_BUTTON. Then no actions should be executed.
	 */
	void cancelScene();

public:
	Map(Renderer* renderer, Country *from_, Country *to_);
	virtual ~Map();

	char getSelection();

private:
	void onKeyDown(SDL_KeyboardEvent e);
	void onKeyUp(SDL_KeyboardEvent e);
	void onMouseButtonDown(SDL_MouseButtonEvent e);
	void onMouseButtonUp(SDL_MouseButtonEvent e);
	void onMouseMotion(SDL_MouseMotionEvent e);
};

