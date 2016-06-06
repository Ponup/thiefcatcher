#ifndef ASSIGNMENTSCREEN_H_
#define ASSIGNMENTSCREEN_H_

#include <Window.h>
#include <Font.h>

#include "screens/ComputerScreen.h"
#include "ui/widgets/InputBox.h"
#include "entities/PlayerCase.h"

class AssignmentScreen : public ComputerScreen {
	
private:
	InputBox *input;

	Font fontInput;
	
        string askName(bool &quitted);
        
public:
	AssignmentScreen(Window *window);
	virtual ~AssignmentScreen();

	PlayerCase *show();
};

#endif

