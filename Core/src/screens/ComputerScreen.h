#ifndef COMPUTERSCREEN_H_
#define COMPUTERSCREEN_H_

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <SDL2/SDL.h>

#include <Font.h>
#include <Surface.h>
#include <Window.h>

class ComputerScreen {

private:
	vector<string> lines;
	
	int currentLine;

	Font *font;
		

protected:
	Window* window;
	Surface *bgSurf;
	
	int readKey();
	
public:
	ComputerScreen(Window *window_);
	virtual ~ComputerScreen();
	
	void clear();	
	void addLine(string line);
	void showLines();
	
	void waitKey();
};

#endif

