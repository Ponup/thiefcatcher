#pragma once

#include <utility>
using std::pair;

struct GeoCoordinates {
    double latitude, longitude;

    pair<double, double> toPair() {
        return {latitude, longitude};
    }

    Point toScreenCoordinates() {
        // y = ((-1 * lat) + 90) * (MAP_HEIGHT / 180);
        // x = ( lon + 180) * (MAP_WIDTH / 360);
        Point point;
        point.y = (int)(((-1 * latitude) + 90) * 2.6);
        point.x = (int)((longitude + 180) * (720 / 360));
        return point;
    }
};
