#pragma once

#include <string>
using std::string;

#include "entities/Criminal.h"

class CriminalFormatter {

public:
	static string formatGenre(const Criminal &criminal);
	static string formatGenre(Genre genre);
	static string formatGenreArticle(const Criminal &criminal, bool capitalizeFirst);
	static string formatGenrePossessive(const Criminal &criminal);
};
