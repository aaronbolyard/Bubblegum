// BUBBLEGUM/internal/solid_brush
//
// Internal declarations for solid brush.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef BUBBLEGUM_INTERNAL_SOLID_BRUSH_H
#define BUBBLEGUM_INTERNAL_SOLID_BRUSH_H

#include "bubblegum/brush.h"
#include "bubblegum/bubblegum.h"
#include "bubblegum/solid_brush.h"
#include "internal/brush.h"

struct BUBBLEGUM_SOLID_BRUSH
{
	BUBBLEGUM_BRUSH brush;

	// The color of the brush.
	BUBBLEGUM_COLOR color;
};

#endif
