#include "Clue.h"

#include <stdlib.h>
#include <string.h>

Clue::Clue() {
}

Clue::Clue( string message ) {
	setMessage(message);
}

void Clue::setMessage( string message ) {
	this->message = message;
}

string Clue::getMessage() const {
	return message;
}

Clue::~Clue() {
}

