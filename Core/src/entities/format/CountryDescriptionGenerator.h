#pragma once

#include <string>
using std::string;

#include "entities/Country.h"

class CountryDescriptionGenerator {

public:
    string generateDescription(const Country& country) const;
};
