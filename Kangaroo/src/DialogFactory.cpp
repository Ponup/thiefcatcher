#include "DialogFactory.h"

#include "components/ConfirmationDialog.h"
#include "components/InformationDialog.h"

int DialogFactory::showConfirmationDialog(Window *screen, const char *message) {
	ConfirmationDialog dlg(screen, message);
	return dlg.showGetSelected();
}

void DialogFactory::showInformationDialog(Window *screen, const char *message) {
	InformationDialog dlg(screen, message);
	dlg.show();
}

