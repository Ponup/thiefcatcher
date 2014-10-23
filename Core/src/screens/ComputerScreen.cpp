#include "ComputerScreen.h"

#include <sstream>
using std::stringstream;

#include <algorithm>
using std::reverse;

#include <Text.h>
#include <Dimension.h>

#include <FontManager.h>

ComputerScreen::ComputerScreen(Window *window_) : window(window_) {
	currentLine = 0;
	
	bgSurf = new Surface("resources/images/notebook_background.png");

	font = FontManager::getFont("NotCourierSans-Bold", 14);
	font->setColor(Color(0, 255, 50));
	
	window->drawSurface( bgSurf, Point::Origin );
	window->flip();
}

ComputerScreen::~ComputerScreen() {
	delete bgSurf;
	
	//@TODOdelete font;
}

void ComputerScreen::clear() {
	lines.clear();
	currentLine = 0;
}

vector<string> &split( const string &s, char delim, vector<string> &elems ) {
	stringstream ss( s );
	string item;
	while( getline( ss, item, delim ) ) {
		elems.push_back( item );
	}
	return elems;
}

void ComputerScreen::addLine(string line) {
	vector<string> tokens;
	split( line, ' ', tokens );
	reverse( tokens.begin(), tokens.end() );

	string nextLine;
	while( !tokens.empty() )
	{
		string nextWord = ( nextLine.empty() ? tokens.back() : string(" ") + tokens.back() );
		if( Text( ( nextLine + nextWord ).c_str(), font ).getDimension().w < 550 ) {
			nextLine.append( nextWord );
		}
		else
		{
			lines.push_back( nextLine );
			nextLine = tokens.back();
		}
		tokens.pop_back();
	}

	lines.push_back( nextLine );
}

void ComputerScreen::showLines() {
	int numLines = static_cast<int>(lines.size());
	for (; currentLine < numLines; currentLine++) {
		Surface* canvas = new Surface( bgSurf->toSDL() );

		int ymin = 120;
		int y = 400;
		for (int x = currentLine; x >= 0; x--) {
			Text text(lines.at(x).c_str(), font);
			text.draw(Point(120, y), canvas);

			y -= font->getLineSkip();
			if (y < ymin) {
				break;
			}
		}

		window->drawSurface( canvas );
		delete canvas;
		window->flip();
		SDL_Delay(250);
	}
}

int ComputerScreen::readKey() {
	int key = SDLK_ESCAPE;

	bool quit = false;
	SDL_Event e;

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_KEYDOWN) {
				key = e.key.keysym.sym;
				quit = true;
			}
		}
		SDL_Delay(80);
	}

	return key;
}

void ComputerScreen::waitKey() {
	readKey();
}

