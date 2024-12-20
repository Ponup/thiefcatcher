#pragma once

#include <SDL.h>

namespace Kangaroo {

	class MouseCursor {

		SDL_Cursor* internal;

	public:
		MouseCursor(SDL_SystemCursor cursorId);
		~MouseCursor();

		void applyToWindow() const;
	};
}