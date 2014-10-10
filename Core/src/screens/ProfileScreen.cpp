#include "ProfileScreen.h"

#include <stdio.h>

#include <System.h>
#include <FontManager.h>

#include <MediaSound.h>

#include <DialogFactory.h>
#include <FrameRegulator.h>

#include <Text.h>

#include <components/InformationDialog.h>

#include "utilities/fx/Sprites.h"
#include "utilities/fx/Sprite.h"
#include "utilities/Translator.h"

#include "entities/CriminalsManager.h"
#include "entities/format/CriminalFormatter.h"

#include "ui/Transitions.h"

ProfileScreen::ProfileScreen(Window *screen_, PlayerCase *playerCase_) :
	screen(screen_), playerCase(playerCase_) {

	option = 0;

	genreIndex = hairIndex = hobbyIndex = featureIndex = 0;

	fontHeader.load("resources/fonts/FreeSansBold.ttf", 20);
	fontHeader.setColor(Color(255, 255, 255));
	
	fontOptions.load("resources/fonts/FreeSans.ttf", 14);
	fontOptions.setColor(Color(200, 225, 240));
	
	fontButtons.load("resources/fonts/FreeSansBold.ttf", 16);
	fontButtons.setColor(Color(95, 175, 230));
	
	hairsList = CriminalsManager::findAllHairs();
	hobbiesList = CriminalsManager::findAllHobbies();
	featuresList = CriminalsManager::findAllFeatures();
	
	quit = false;
			
	bgSurface.load("resources/images/notebook_background.png");
	
	drawElements();
	
	//Transitions::slideBT(screen, screen->getArea());
}

ProfileScreen::~ProfileScreen() {
	hairsList.clear();
	hobbiesList.clear();
	featuresList.clear();
}

int ProfileScreen::run() {
	FrameRegulator fr(100);
	fr.setUp();

	while (quit == false) {
		captureEvents();	
		drawElements();
		screen->flip();

		fr.regulate();
	}

	return returnCode;
}

void ProfileScreen::drawElements() {
	screen->drawSurface(&bgSurface, Point(0, 0));

	int marginLeft = 150;
	int marginTop = 190;
	
	Text text;

	if(playerCase->captureOrderExecuted) {
		char message[100];
		sprintf(message, _("You capture order was executed against '%s'").c_str(), playerCase->getCriminal().getName());
		text.setFont(&fontOptions);
		text.setText(message);
		text.draw(Point(120, 200), screen);
	} else {
		text.setFont(&fontHeader);
		text.setText("Capture order");
		text.draw(Point(500, 120), screen);
		// 0: sex, 1: hair, 2: hobby, 3: features, 4: capture, 5: cancel
	
		text.setFont(&fontOptions);
		text.setText(_("Genre"));
		text.draw(Point(marginLeft, marginTop), screen);
	
		text.setText( CriminalFormatter::formatGenre( static_cast<Genre>( genreIndex ) ) );
		text.draw(Point(230, marginTop), screen);
		sensAreas.addArea(Point(230, marginTop), text.getDimension()); // Genre: 0
	
		marginTop += 50;
		text.setText("Hair");
		text.draw(Point(marginLeft, marginTop), screen);
			
		text.setText(hairsList.at(hairIndex).c_str());
		text.draw(Point(230, marginTop), screen);
		sensAreas.addArea(Point(230, marginTop), text.getDimension()); // Hair: 1

		marginTop += 50;
		text.setText("Hobby");
		text.draw(Point(marginLeft, marginTop), screen);
	
		text.setText(hobbiesList.at(hobbyIndex).c_str());
		text.draw(Point(230, marginTop), screen);
		sensAreas.addArea(Point(230, marginTop), text.getDimension()); // Hobby: 2
	
		marginTop += 50;
		text.setText("Features");
		text.draw(Point(marginLeft, marginTop), screen);
	
		text.setText(featuresList.at(featureIndex).c_str());
		text.draw(Point(230, marginTop), screen);
		sensAreas.addArea(Point(230, marginTop), text.getDimension()); // Feature: 3
	
		text.setFont(&fontButtons);
		text.setText("Execute order");
		text.draw(Point(250, 440), screen);
		sensAreas.addArea(Point(250, 440), text.getDimension()); // Execute: 4
	
		text.setText("Save and close");
		text.draw(Point(450, 440), screen);
		sensAreas.addArea(Point(450, 440), text.getDimension()); // Cancel: 5
	}
}

void ProfileScreen::onQuit(SDL_QuitEvent e) {
	quit = true;
	returnCode = -1;
}

void ProfileScreen::onMouseMotion(SDL_MouseMotionEvent event) {
}

void ProfileScreen::onMouseButtonDown(SDL_MouseButtonEvent event) {
	if (event.button == SDL_BUTTON_RIGHT) {
		quit = true;
		returnCode = -1;
	} else {
		int resolved = sensAreas.resolve(event.x, event.y);
		switch (resolved) {
		case -1:
			break;
		case 0:
			if (++genreIndex == 2) {
				genreIndex = 0;
			}
			break;
		case 1:
			if (++hairIndex >= hairsList.size()) {
				hairIndex = 0;
			}
			break;
		case 2:
			if (++hobbyIndex >= hobbiesList.size()) {
				hobbyIndex = 0;
			}
			break;
		case 3:
			if (++featureIndex >= featuresList.size()) {
				featureIndex = 0;
			}
			break;
		case 4: {
			screen->drawSurface(&bgSurface, Point(0, 0));
			
			Dimension spriteDim(128, 15);
			
			Text text;
			text.setFont(&fontHeader);
			text.setText("Looking the database of criminals...");
			text.draw(Point(400 - (text.getDimension().w >> 1), 250), screen);
			
			screen->flip();
			
			Sprite sprite("resources/images/sprites/frame%d.png", 12, spriteDim);
			sprite.setPosition(Point(400 - 64, 280));

			MediaSound computerSound("resources/sounds/computer.wav");
			computerSound.play();
						
			int milliSeconds = 0;
			while(milliSeconds < 4000) {
				sprite.draw(screen);
				sprite.update(screen);
				milliSeconds += 30;

				SDL_Delay(30);
			}
			
			Criminal *criminal = CriminalsManager::findByFeatures(
					static_cast<Genre>( genreIndex ),
					hobbiesList[hobbyIndex].c_str(),
					hairsList[hairIndex].c_str() );
			if (!criminal) {
				InformationDialog dlg(screen, _("The combination does not match with an existent thief profile."));
				dlg.show();
			} else if (criminal->getID() == playerCase->getCriminal().getID()) {
				char message[100];
				sprintf(message, _("Your capture order was succesfuly executed against '%s'!").c_str(), criminal->getName());
				InformationDialog dlg(screen, message);
				dlg.show();
				playerCase->captureOrderExecuted = true;
				quit = true;
			} else {
				InformationDialog dlg(screen, _("You commited a capture order against the wrong criminal!"));
				dlg.show();
			}
			break;
		}
		case 5:
			quit = true;
		default:
			break;
		}
	}
}

void ProfileScreen::onMouseButtonUp(SDL_MouseButtonEvent event) {
}

void ProfileScreen::onKeyDown(SDL_KeyboardEvent event) {
	// 0: sex, 1: hair, 2: hobby, 3: features, 4: capture, 5: cancel
	switch (event.keysym.sym) {
	case SDLK_ESCAPE:
		quit = true;
		break;
	case SDLK_UP:
		if (option > 0) {
			option--;
		}
		printf("Up\n");
		break;
	case SDLK_DOWN:
		if (option < 5) {
			option++;
		}
		printf("Down\n");
		break;
	case SDLK_RIGHT:
		break;
	case SDLK_LEFT:
		break;
	case SDLK_RETURN:
		printf("Enter\n");
		switch (option) {
		case 4:
			printf("Executing capture order\n");
			quit = true;
		case 5:
			printf("Cancelling dialog\n");
			quit = true;
			break;
		}
		break;
	default:
		printf("Ignoring key...\n");
		break;
	}
	printf("Option: %d\n", option);
}

void ProfileScreen::onKeyUp(SDL_KeyboardEvent event) {
}
