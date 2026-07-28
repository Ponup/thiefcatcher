#include "MouseCursor.h"

Kangaroo::MouseCursor::MouseCursor(SDL_SystemCursor cursorId) {
	internal = SDL_CreateSystemCursor(cursorId);
}

Kangaroo::MouseCursor::~MouseCursor() {
	SDL_DestroyCursor(internal);
}

void Kangaroo::MouseCursor::applyToWindow() const {
	SDL_SetCursor(internal);
}
