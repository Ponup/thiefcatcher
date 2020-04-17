#include "CountryDescriptionGenerator.h"

#include <sstream>
using std::ostringstream;

#include <fmt/format.h>

string CountryDescriptionGenerator::generateDescription(const Country& country) const {
    ostringstream oss;

    oss << fmt::format("{0} is a country located in {1}.", country.getName(), country.getContinent());
    oss << fmt::format(" Its capital city is {0}.", country.getCapital());
    oss << fmt::format(" Its flag is described as {0}.", country.getFlag());

    return oss.str();
}
