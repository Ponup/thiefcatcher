#pragma once

#include <string>
using std::string;

#include "entities/Criminal.h"

class GenreFormatter {

public:
	static string format(const Genre& genre);
	static string formatSubjectPronoun(const Genre &genre);
	static string formatObjectPronoun(const Genre &genre);
	static string formatPossessiveAdjective(const Genre &genre);
};
