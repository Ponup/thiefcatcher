#include "Menu.h"

#include <FrameRegulator.h>
#include <utilities/fx/Sprite.h>
#include <MediaSound.h>

#include "utilities/Translator.h"

#include "Renderer.h"
#include "Texture.h"

using Kangaroo::Renderer;
using Kangaroo::Texture;

Menu::Menu(Window * window_) :
	selectedItem(0),
	window(window_),
	backgroundTexture(window_->renderer, "resources/images/menu/background.png"),
	smokingPipeTexture(window_->renderer, "resources/images/menu/pipe.png"),
	normalCursor(SDL_SYSTEM_CURSOR_ARROW),
	handCursor(SDL_SYSTEM_CURSOR_HAND)
{
	lastY = 150;
	currentItem = -2;

	sound.load("resources/sounds/step.wav");

	// Fonts
	headerFont.load("resources/fonts/gtw.ttf", 45);
	headerFont.setColor(Color(255, 220, 220));
	font.load("resources/fonts/FreeSansBold.ttf", 30);
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
	Text text(item, &font);
	Dimension dim = text.getDimension();
	Point position(400 - (dim.w >> 1), lastY);

	sensAreas.addArea(Area(position, dim));

	MenuItem menuItem;
	menuItem.setText(text);
	menuItem.setPosition(position);

	items.push_back(menuItem);

	lastY = lastY + dim.h + 5;

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

	normalCursor.applyToWindow();

	return selectedItem;
}

void Menu::update() {
	Color colorSelected(255, 255, 255);
	Color colorNotSelected(0x3f, 0x24, 0x12);

	Renderer renderer(window->renderer);

	renderer.drawTexture(&backgroundTexture);

	Text textLine(_("Thief Catcher"));
	textLine.setFont(&headerFont);
	renderer.drawText(&textLine, Point(30, 10));

	for (unsigned int i = 0; i < items.size(); i++) {
		MenuItem item = items.at(i);
		Text text = item.getText();
		if ((short)i == selectedItem) {
			renderer.drawTexture(&smokingPipeTexture, Point(185, item.getPosition().y));
			font.setColor(colorSelected);
		}
		else {
			font.setColor(colorNotSelected);
		}
		text.setFont(&font);
		renderer.drawText(&text, item.getPosition());
	}

	renderer.present();
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
		if (selectedItem < (int)items.size() - 1) {
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
	if (resolved == -1)
		normalCursor.applyToWindow();
	else
		handCursor.applyToWindow();
	if (resolved != -1 && resolved != selectedItem) {
		sound.play();
		selectedItem = resolved;
	}
}

