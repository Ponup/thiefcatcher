#include "Clue.h"

Clue::Clue() {
}

Clue::~Clue() {
}

Clue::Clue( const string &message ) {
	setMessage(message);
}

void Clue::setMessage( const string &message ) {
	this->message = message;
}

string Clue::getMessage() const {
	return message;
}

