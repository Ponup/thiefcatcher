#include "Menu.h"

#include <System.h>
#include <FrameRegulator.h>
#include <utilities/fx/Sprite.h>
#include <MediaSound.h>

Menu::Menu(Surface * window_) :
	selectedItem(0), window(window_) {
	lastY = 150;
	currentItem = -2;
	
	sound.load("resources/sounds/menu.wav");

	font.load("resources/fonts/FreeSansBold.ttf", 30);
	
	backgroundSurf.load("resources/images/menu/background.png");
	pipeSurf.load("resources/images/menu/pipe.png");
}

Menu::~Menu() {
	items.clear();
}

void Menu::reset() {
	currentItem = -2;
}

void Menu::setSelectedItem(short selectedItem) {
	this->selectedItem = selectedItem;
}

short Menu::addItem(string item) {
	Text *text = new Text(item, &font);
	Dimension dim = text->getDimension();
	Point position((window->getDimension().getWidth() >> 1) - (dim.getWidth() >> 1), lastY);

	sensAreas.addArea(Area(position, dim));

	MenuItem menuItem;
	menuItem.setText(text);
	menuItem.setPosition(position);

	items.push_back(menuItem);

	lastY = lastY + dim.getHeight() + 5;
	
	return items.size() - 1;
}

short Menu::getSelectedItem() {
	FrameRegulator fr(150);
	fr.setUp();

	update();
	while (currentItem == -2) {
		captureEvents();
		update();
		fr.regulate();
	}

	return selectedItem;
}

void Menu::update() {
	Color colorSelected(255, 255, 255);
	Color colorNotSelected(63, 36, 18); // #3f2412
		
	window->drawSurface(&backgroundSurf, Point(0, 0));
	
	for (unsigned int i = 0; i < items.size(); i++) {
		MenuItem item = items.at(i);
		Text *text = item.getText();
		if ((short)i == selectedItem) {
			window->drawSurface(&pipeSurf, Point(185, item.getPosition().getY()));
			font.setColor(colorSelected);
		} else {
			font.setColor(colorNotSelected);
		}
		text->setFont(&font);
		text->draw(item.getPosition(), window);
	}
	
	window->flip();
}

void Menu::onQuit(SDL_QuitEvent e) {
	currentItem = selectedItem = 5;
}

void Menu::onKeyDown(SDL_KeyboardEvent key) {
	switch (key.keysym.sym) {
	case SDLK_UP:
		if (selectedItem > 0) {
			selectedItem--;
			sound.play();
		}
		break;
	case SDLK_DOWN:
		if (selectedItem < (int)items.size()-1) {
			selectedItem++;
			sound.play();
		}
		break;
	case SDLK_RETURN:
		currentItem = selectedItem;
		break;
	case SDLK_ESCAPE:
		currentItem = selectedItem = 5;  
		break;
	default:
		break;
	}
}

void Menu::onKeyUp(SDL_KeyboardEvent e) {

}

void Menu::onMouseButtonDown(SDL_MouseButtonEvent button) {
	if (button.button == SDL_BUTTON_LEFT) {
		int resolved = sensAreas.resolve(button.x, button.y);
		if (resolved != -1) {
			currentItem = resolved;
		}
	}
}

void Menu::onMouseButtonUp(SDL_MouseButtonEvent e) {

}

void Menu::onMouseMotion(SDL_MouseMotionEvent motion) {
	int resolved = sensAreas.resolve(motion.x, motion.y);
	if (resolved != -1 && resolved != selectedItem) {
		sound.play();
		selectedItem = resolved;
	}
}

