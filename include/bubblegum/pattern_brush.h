// BUBBLEGUM/pattern_brush
//
// Declarations for pattern brushes.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef BUBBLEGUM_PATTERN_BRUSH_H
#define BUBBLEGUM_PATTERN_BRUSH_H

#include <stdint.h>
#include "bubblegum/bubblegum.h"
#include "bubblegum/brush.h"

typedef struct BUBBLEGUM_PATTERN_BRUSH BUBBLEGUM_PATTERN_BRUSH;

/// Creates a BUBBLEGUM_PATTERN_BRUSH for the provided context.
BUBBLEGUM_API BUBBLEGUM_PATTERN_BRUSH * bg_create_pattern_brush(BUBBLEGUM_CONTEXT *context);

/// Converts a BUBBLEGUM_BRUSH to a BUBBLEGUM_PATTERN_BRUSH.
///
/// If the conversion fails (i.e., the brush is not a linear gradient), this
/// method returns NULL.
BUBBLEGUM_API BUBBLEGUM_PATTERN_BRUSH * bg_to_pattern_brush(
	BUBBLEGUM_BRUSH *brush);

/// Converts a BUBBLEGUM_PATTERN_BRUSH to a BUBBLEGUM_BRUSH.
BUBBLEGUM_API BUBBLEGUM_BRUSH * bg_from_pattern_brush(BUBBLEGUM_PATTERN_BRUSH *brush);

BUBBLEGUM_API void bg_set_pattern_brush_pattern(
	BUBBLEGUM_PATTERN_BRUSH *brush,
	BUBBLEGUM_CANVAS *canvas);
BUBBLEGUM_API BUBBLEGUM_CANVAS * bg_get_pattern_brush_pattern(BUBBLEGUM_PATTERN_BRUSH *brush);

BUBBLEGUM_API void bg_set_pattern_brush_rotation(BUBBLEGUM_PATTERN_BRUSH *brush, float value);
BUBBLEGUM_API float bg_get_pattern_brush_rotation(BUBBLEGUM_PATTERN_BRUSH *brush);
BUBBLEGUM_API void bg_set_pattern_brush_offset_x(BUBBLEGUM_PATTERN_BRUSH *brush, float value);
BUBBLEGUM_API float bg_get_pattern_brush_offset_x(BUBBLEGUM_PATTERN_BRUSH *brush);
BUBBLEGUM_API void bg_set_pattern_brush_offset_y(BUBBLEGUM_PATTERN_BRUSH *brush, float value);
BUBBLEGUM_API float bg_get_pattern_brush_offset_y(BUBBLEGUM_PATTERN_BRUSH *brush);
BUBBLEGUM_API void bg_set_pattern_brush_scale_x(BUBBLEGUM_PATTERN_BRUSH *brush, float value);
BUBBLEGUM_API float bg_get_pattern_brush_scale_x(BUBBLEGUM_PATTERN_BRUSH *brush);
BUBBLEGUM_API void bg_set_pattern_brush_scale_y(BUBBLEGUM_PATTERN_BRUSH *brush, float value);
BUBBLEGUM_API float bg_get_pattern_brush_scale_y(BUBBLEGUM_PATTERN_BRUSH *brush);

#endif
