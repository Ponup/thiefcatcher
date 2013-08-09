#ifndef MAP_H
#define MAP_H

#include <EventHandler.h>
#include <SensitiveAreas.h>
#include <Surface.h>
#include <Font.h>
#include <Dimension.h>
#include <Point.h>

#include "entities/Country.h"

class Map : public EventHandler {

	private:
		SensitiveAreas sensAreas;
		int selected;
		bool quit;
		
		Country *from;
		Country *to;
		
		Surface *window;

		Surface airplane;		

		Font font;
		
		Dimension airplaneDim;
		
		Surface map;
		Surface target;
		Surface target_over;
		Point points[3];
		
		void updateScreen(bool update);
		void gotoTarget();
		
		/**
		 * This method is called when the user presses ESCAPE or RIGHT_BUTTON. Then no actions should be executed.
		 */
		void cancelScene();
		
	public:
		Map(Surface *window_, Country *from_, Country *to_);
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

