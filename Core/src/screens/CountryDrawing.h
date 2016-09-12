#pragma once

#include <Surface.h>
#include <Renderer.h>

using Kangaroo::Renderer;

#include "entities/Country.h"

void drawCountry(Renderer* renderer, const Country &country);
