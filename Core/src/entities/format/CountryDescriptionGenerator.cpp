#include "CountryDescriptionGenerator.h"

#include <sstream>
using std::ostringstream;

#include <fmt/format.h>

string CountryDescriptionGenerator::generateDescription(const Country& country) const {
    ostringstream oss;

    oss << fmt::format("{0} is a country located in {1}. Its capital city is {2}.", country.getName(), country.getContinent(), country.getCapital());

    return oss.str();
}
