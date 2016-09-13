#pragma once

#include <Renderer.h>
using Kangaroo::Renderer;

#include "entities/Country.h"

void drawCountry(Renderer* renderer, const Country &country, bool drawDescription = false);
