// BUBBLEGUM/gradient_brush
//
// Declarations for gradient brushes.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef BUBBLEGUM_GRADIENT_BRUSH_H
#define BUBBLEGUM_GRADIENT_BRUSH_H

#include "bubblegum/bubblegum.h"
#include "bubblegum/brush.h"

typedef struct BUBBLEGUM_GRADIENT_BRUSH BUBBLEGUM_GRADIENT_BRUSH;

enum BUBBLEGUM_GRADIENT_BRUSH_DRAW_MODE
{
	BUBBLEGUM_GRADIENT_BRUSH_DRAW_MODE_LINEAR = 0,
	BUBBLEGUM_GRADIENT_BRUSH_DRAW_MODE_RADIAL
};

/// Creates a BUBBLEGUM_GRADIENT_BRUSH for the provided context.
BUBBLEGUM_API BUBBLEGUM_GRADIENT_BRUSH * bg_create_gradient_brush(
	BUBBLEGUM_CONTEXT *context);

/// Converts a BUBBLEGUM_BRUSH to a BUBBLEGUM_GRADIENT_BRUSH.
///
/// If the conversion fails (i.e., the brush is not a linear gradient), this
/// method returns NULL.
BUBBLEGUM_API BUBBLEGUM_GRADIENT_BRUSH * bg_to_gradient_brush(
	BUBBLEGUM_BRUSH *brush);

/// Converts the BUBBLEGUM_GRADIENT_BRUSH to a BUBBLEGUM_BRUSH.
BUBBLEGUM_API BUBBLEGUM_BRUSH * bg_from_radial_gradient_brush(BUBBLEGUM_GRADIENT_BRUSH *brush);

/// Sets the brush draw mode.
///
/// The value should be one of the BUBBLEGUM_GRADIENT_BRUSH_DRAW_MODE enumerations.
BUBBLEGUM_API void bg_set_gradient_brush_draw_mode(BUBBLEGUM_GRADIENT_BRUSH *brush, int value);

/// Returns the brush draw mode.
///
/// The default value is BUBBLEGUM_GRADIENT_BRUSH_DRAW_MODE_LINEAR.
BUBBLEGUM_API int bg_get_gradient_brush_draw_mode(BUBBLEGUM_GRADIENT_BRUSH *brush);

/// Appends a stop to the gradient with the provided color and offset.
///
/// Offset will be clamped to the offset of the previous stop, or 0 if no
/// previous stop is defined. If the value exceeds 1, it will be clamped as
/// well.
BUBBLEGUM_API void bg_add_gradient_stop(
	BUBBLEGUM_GRADIENT_BRUSH *brush,
	BUBBLEGUM_COLOR *color,
	float offset);

/// Inserts a stop before the provided index.
///
/// Offset will be clamped to the offset of the previous stop, or 0 if no
/// previous stop is defined, as well as the offset of the next stop, or 1 if no
/// step follows.
BUBBLEGUM_API void bg_insert_gradient_stop(
	BUBBLEGUM_GRADIENT_BRUSH *brush,
	int index,
	BUBBLEGUM_COLOR *color,
	float offset);

/// Removes the stop at the provided index. Does nothing if index is out-of-bounds.
BUBBLEGUM_API void bg_remove_gradient_brush_stop(
	BUBBLEGUM_GRADIENT_BRUSH *brush,
	int index);

/// Gets the number of linear gradient stops.
BUBBLEGUM_API int bg_get_num_gradient_stops(BUBBLEGUM_GRADIENT_BRUSH *brush);

/// Gets the offset of the stop at the provided index.
///
/// If index is out-of-bounds, returns NaN.
BUBBLEGUM_API float bg_get_gradient_stop_offset(
	BUBBLEGUM_GRADIENT_BRUSH *brush,
	int index);

/// Gets the stop color.
///
/// If index is out-of-bounds, returns bg_get_invalid_color().
BUBBLEGUM_API BUBBLEGUM_COLOR bg_get_gradient_stop_color(
	BUBBLEGUM_GRADIENT_BRUSH *brush,
	int index);

#endif
