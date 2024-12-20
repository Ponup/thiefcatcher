#include "Dimension.h"

ostream& operator<<(ostream& stream, const Dimension& dimension) {
	return stream << "Dimension {w: " << dimension.w << ", h: " << dimension.h << "}";
}

