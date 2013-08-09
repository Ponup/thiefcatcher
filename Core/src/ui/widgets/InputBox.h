#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <SDL.h>
#include <Surface.h>
#include <FontManager.h>
#include <Text.h>

#include <string>
using std::string;

class InputBox {
	private:
		string text;
		Text line;
		Color background;
		Color foreground;

		Surface *window;
		Surface *area;
		Font *font;
		Point point;
		Dimension dimension;
		
		unsigned short maxChars;
		
		Surface *backup;
		
	public:
		InputBox();
		InputBox(Surface *dialog_, Font *font_, const Point &point_, const Dimension &dimension_);
		~InputBox();
		
		void setBackground(const Color &background);
		void setForeground(const Color &foreground);
		void setFont(Font *font);
		void handleEvent(SDL_Event &event);
		void update();
		
		void setMaxChars(unsigned short maxChars);
		unsigned short getMaxChars() const;
		
		char *getText();
		char *get();
		
		void clear();
};

#endif

