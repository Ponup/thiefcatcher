#include "components/InformationDialog.h"

#include "FontManager.h"
#include "SurfaceUtil.h"

InformationDialog::InformationDialog(Window *screen_, const string& message_) : message(message_) {
}

InformationDialog::~InformationDialog() {}

void InformationDialog::show() {
	const SDL_MessageBoxButtonData buttons[] = {
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, DIALOG_YES, "Ok" },
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		nullptr, /* .window */
		"Information", /* .title */
		message.c_str(), /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&defaultColorScheme /* .colorScheme */
	};
	int buttonid;
	SDL_ShowMessageBox(&messageboxdata, &buttonid);
}

