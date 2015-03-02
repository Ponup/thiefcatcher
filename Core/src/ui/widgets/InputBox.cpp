#include "InputBox.h"

InputBox::InputBox() {
}

InputBox::InputBox(Surface *dialog_, Font *font_, const Point &point_,
		const Dimension &dimension_) :
	window(dialog_), font(font_), point(point_), dimension(dimension_) {
	background = Color(255, 255, 255);

	line = Text("", font);

	backup = window->getArea(point, dimension);
	area = window->getArea(point, dimension);

//	SDL_EnableUNICODE(1);
//	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	setMaxChars(25);
}

InputBox::~InputBox() {
//	SDL_EnableKeyRepeat(0, 0);
//	SDL_EnableUNICODE(0);
}

void InputBox::setBackground(const Color & background) {
	this->background = background;
}

void InputBox::setForeground(const Color & foreground) {
	this->foreground = foreground;
}

void InputBox::setFont(Font * font) {
	this->font = font;
	this->font->setColor(foreground);

	line.setFont(font);
}

string InputBox::getText() {
	return text;
}

void InputBox::handleEvent(SDL_Event & e) {
	if (e.type == SDL_KEYDOWN) {
		int key = e.key.keysym.sym;
		if (text.size() < maxChars && ((key >= SDLK_a && key <= SDLK_z) || (key
				>= SDLK_0 && key <= SDLK_9) || key == SDLK_SPACE)) {
			text += e.key.keysym.sym;
		} else if (key == SDLK_BACKSPACE) {
			text = text.substr(0, text.size()-1);
		}
	}
}

void InputBox::update() {
	if(true)return;
	area->drawSurface( backup );
	line.draw( Point::Origin, area );
	window->drawSurface(area, point);
	window->updateArea(point, dimension);
}

void InputBox::setMaxChars(unsigned short maxChars) {
	this->maxChars = maxChars;
}

unsigned short InputBox::getMaxChars() const {
	return maxChars;
}

string InputBox::get() {
	SDL_Event event;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_RETURN) {
					quit = true;
				}
				break;
			}
			handleEvent(event);
			line.setText(text.c_str());
			update();
		}
		SDL_Delay(100);
	}

	return getText();
}

void InputBox::clear() {
	text.clear();
}
