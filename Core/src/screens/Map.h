#ifndef MAP_H
#define MAP_H

#include <EventHandler.h>
#include <SensitiveAreas.h>
#include <Surface.h>
#include <Window.h>
#include <Font.h>
#include <Dimension.h>
#include <Point.h>

#include "entities/Country.h"

class Map : public EventHandler {

	private:
		SensitiveAreas sensAreas;
		int selected;
		bool quit;
		bool updatePending;
		
		Country* sourceCountry;
		Country* targetCountry;
		
		Window* window;
		Surface* canvas;
		Surface* bgSurface;

		Surface *directedAirplane;

		Font font;
		
		Dimension airplaneDim;
		Point airplanePosition;

		Point mapOffset;
		Point offsetFix;
		Surface map;

		Point bulletRadius;
		Surface bulletSurface;
		Surface bulletOverSurface;

		Point points[3];
		
		void addSensibleAreas();
		void drawAllCountries();
		void createStaticBackground();
		void drawOptions();
		void drawDirectedAirplane();
		void updateScreen(bool update);
		void gotoTarget();
		
		/**
		 * This method is called when the user presses ESCAPE or RIGHT_BUTTON. Then no actions should be executed.
		 */
		void cancelScene();
		
	public:
		Map(Window *window_, Country *from_, Country *to_);
		virtual ~Map();
		
		char getSelection();
	
	private:
		void onKeyDown(SDL_KeyboardEvent e);
		void onKeyUp(SDL_KeyboardEvent e);
		void onMouseButtonDown(SDL_MouseButtonEvent e);
		void onMouseButtonUp(SDL_MouseButtonEvent e);
		void onMouseMotion(SDL_MouseMotionEvent e);
};

#endif

