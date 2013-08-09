#include "ComputerScreen.h"

#include <Text.h>
#include <Dimension.h>

#include <FontManager.h>

ComputerScreen::ComputerScreen(Window *window_) : window(window_) {
	
	currentLine = 0;
	
	bgSurf = new Surface("resources/images/notebook_background.png");

	font = FontManager::getFont("FreeSansBold", 14);
	font->setColor(Color(0, 255, 50));
	
	window->drawSurface(bgSurf, Point(0, 0));
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

void ComputerScreen::addLine(const char *line) {
	char *backup = strdup(line);
	string validLine;
	char *token = strtok(backup, " ");
	while (token != NULL) {
		string temp = validLine;
		if (temp.empty() == false) {
			temp += " ";
		}
		temp += token;

		Text text(temp.c_str(), font);
		Dimension dim = text.getDimension();
		if (dim.getWidth() < 550) {
			validLine = temp;
		} else {
			lines.push_back(validLine);
			validLine = token;
		}

		token = strtok(NULL, " ");
	}

	lines.push_back(validLine);
	
	free(backup);
}

void ComputerScreen::showLines() {
	int numLines = static_cast<int>(lines.size());
	for (; currentLine < numLines; currentLine++) {
		window->drawSurface(bgSurf, Point(0, 0));

		int ymin = 120;
		int y = 400;
		for (int x = currentLine; x >= 0; x--) {
			Text text(lines.at(x).c_str(), font);
			text.draw(Point(120, y), window);

			y -= font->getLineSkip();
			if (y < ymin) {
				break;
			}
		}

		window->flip();
		SDL_Delay(250);
	}
}

SDLKey ComputerScreen::readKey() {
	SDLKey key = SDLK_ESCAPE;

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
