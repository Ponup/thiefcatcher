#include "SensitiveAreas.h"

void SensitiveAreas::addArea(const Area & area) {
	areas.push_back(area);
}

void SensitiveAreas::addArea(const Point & point, const Dimension & dimension) {
	areas.push_back(Area(point, dimension));
}

int SensitiveAreas::resolve(int x, int y) const {
	int resolved = -1;
	unsigned int areasSize = areas.size();
	for(unsigned int i = 0; i < areasSize; i++) {
		if(areas.at(i).contains(x, y)) {
			return i;
		}
	}
	return resolved;
}

