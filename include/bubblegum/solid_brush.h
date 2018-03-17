// BUBBLEGUM/solid_brush
//
// Declarations for solid brushes.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef BUBBLEGUM_SOLID_BRUSH_H
#define BUBBLEGUM_SOLID_BRUSH_H

#include "bubblegum/bubblegum.h"
#include "bubblegum/brush.h"

typedef struct BUBBLEGUM_SOLID_BRUSH BUBBLEGUM_SOLID_BRUSH;

/// Creates a solid brush.
///
/// The color is set white (1, 1, 1, 1).
///
/// Returns the brush on success, or NULL on failure.
BUBBLEGUM_API
BUBBLEGUM_API BUBBLEGUM_SOLID_BRUSH * bg_create_solid_brush(BUBBLEGUM_CONTEXT *context);

/// Converts a BUBBLEGUM_BRUSH to a BUBBLEGUM_SOLID_BRUSH.
///
/// If the conversion fails (i.e., the brush is not a linear gradient), this
/// method returns NULL.
BUBBLEGUM_API
BUBBLEGUM_API BUBBLEGUM_SOLID_BRUSH * bg_to_solid_brush(BUBBLEGUM_BRUSH *brush);

/// Converts the BUBBLEGUM_SOLID_BRUSH to a BUBBLEGUM_BRUSH
BUBBLEGUM_API
BUBBLEGUM_API BUBBLEGUM_BRUSH * bg_from_solid_brush(BUBBLEGUM_SOLID_BRUSH *brush);

/// Sets the brush color.
BUBBLEGUM_API
BUBBLEGUM_API void bg_set_solid_brush_color(
	BUBBLEGUM_SOLID_BRUSH *brush,
	const BUBBLEGUM_SOLID_BRUSH *color);

/// Gets the brush color.
BUBBLEGUM_API
BUBBLEGUM_API BUBBLEGUM_COLOR bg_get_solid_brush_color(BUBBLEGUM_SOLID_BRUSH *brush)

#endif
