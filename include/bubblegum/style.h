// BUBBLEGUM/canvas
//
// Declarations for canvas.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef BUBBLEGUM_STYLE_H
#define BUBBLEGUM_STYLE_H

typedef struct BUBBLEGUM_STYLE BUBBLEGUM_STYLE;

/// Creates a Bubblegum style from the context.
BUBBLEGUM_STYLE * bg_create_style(BUBBLEGUM_CONTEXT *context);
void bg_destroy_style(BUBBLEGUM_STYLE *style);

/// Sets the fill brush.
///
/// The default value is NULL (unset). An unset brush inherits the style from
/// the canvas.
void bg_set_fill_brush(BUBBLEGUM_STYLE *style, BUBBLEGUM_BRUSH *value);

/// Gets the fill brush.
BUBBLEGUM_BRUSH * bg_get_fill_brush(BUBBLEGUM_STYLE *style);

/// Sets the stroke brush.
///
/// See bg_set_fill_brush for the semantics.
void bg_set_stroke_brush(BUBBLEGUM_STYLE *style, BUBBLEGUM_BRUSH *value);

/// Gets the stroke brush.
BUBBLEGUM_BRUSH * bg_get_stroke_brush(BUBBLEGUM_STYLE *style);

/// Sets the stroke width.
///
/// Values must be at least 0. A value of 0 means no stroke.
void bg_set_stroke_width(BUBBLEGUM_STYLE *style, float value);

/// Gets the stroke width.
float bg_get_stroke_width(BUBBLEGUM_STYLE *style);

#endif
