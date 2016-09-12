#pragma once

#include <Window.h>
#include <Font.h>

#include "screens/ComputerScreen.h"
#include "ui/widgets/InputBox.h"
#include "entities/PlayerCase.h"

class AssignmentScreen : public ComputerScreen {

	InputBox *input;

	Font fontInput;

	string askName(bool &quitted);

public:
	AssignmentScreen(Renderer* renderer);
	virtual ~AssignmentScreen();

	PlayerCase *show();
};

