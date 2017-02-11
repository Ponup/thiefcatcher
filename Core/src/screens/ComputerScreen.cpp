#include "ComputerScreen.h"

#include <sstream>
using std::stringstream;

#include <algorithm>
using std::reverse;

#include <Text.h>
#include <Dimension.h>

#include <FontManager.h>

ComputerScreen::ComputerScreen(Renderer* renderer) :
	renderer(renderer),
	backgroundTexture(renderer->internal, "resources/images/notebook_background.png")
{
	currentLine = 0;

	font = FontManager::getFont("NotCourierSans-Bold", 14);
	font->setColor(Color(0, 255, 50));
}

ComputerScreen::~ComputerScreen() {
}

void ComputerScreen::clear() {
	lines.clear();
	currentLine = 0;
}

vector<string> &split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

void ComputerScreen::addLine(const string& line) {
	vector<string> tokens;
	split(line, ' ', tokens);
	reverse(tokens.begin(), tokens.end());

	string nextLine;
	while (!tokens.empty()) {
		string nextWord = (nextLine.empty() ? tokens.back() : string(" ") + tokens.back());
		if (Text((nextLine + nextWord).c_str(), font).getDimension().w < 550) {
			nextLine.append(nextWord);
		}
		else {
			lines.push_back(nextLine);
			nextLine = tokens.back();
		}
		tokens.pop_back();
	}

	lines.push_back(nextLine);
}

void ComputerScreen::showLines() {
	vector<string>::size_type numLines = lines.size();
	for (; currentLine < numLines; currentLine++) {
		renderer->drawTexture(&backgroundTexture);

		int ymin = 120;
		int y = 400;
		for (int x = currentLine; x >= 0; x--) {
			Text text(lines.at(x).c_str(), font);
			renderer->drawText(&text, Point(120, y));

			y -= font->getLineSkip();
			if (y < ymin) {
				break;
			}
		}

		renderer->present();
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

void ComputerScreen::waitForInput() {
	bool quit = false;
	SDL_Event ev;

	while (!quit) {
		SDL_Delay(80);
		while (SDL_PollEvent(&ev)) {
			quit = ev.type == SDL_KEYDOWN || ev.type == SDL_MOUSEBUTTONDOWN;
		}
	}
}

