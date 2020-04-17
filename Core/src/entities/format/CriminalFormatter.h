#pragma once

#include <string>
using std::string;

#include "entities/Criminal.h"

class CriminalFormatter {

public:
	static string formatGenre(const Criminal &criminal);
	static string formatGenre(const Genre& genre);
	static string formatGenreArticle(const Criminal &criminal);
	static string formatGenrePossessive(const Criminal &criminal);
};
