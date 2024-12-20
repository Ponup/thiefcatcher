#pragma once

#include "Renderer.h"
#include "Text.h"
#include "Point.h"

using namespace Kangaroo;

namespace Kangaroo {

	class TextUtils {
	public:
		void drawLines(Renderer* renderer, const Text& text, const Point& position, const Dimension& containerDimension) const;
	};
}
