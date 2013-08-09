#include "Clue.h"

#include <stdlib.h>
#include <string.h>

Clue::Clue() {
	message = NULL;
}

Clue::Clue(const char *message) {
	setMessage(message);
}

void Clue::setMessage(const char *message) {
	this->message = strdup( message );
}

const char *Clue::getMessage() const {
	return strdup(message);
}

Clue::~Clue() {
	if(message)
	{
		free(message);
	}
	message = NULL;
}

