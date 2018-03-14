// BUBBLEGUM/texture_brush
//
// Declarations for texture brushes.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef BUBBLEGUM_TEXTURE_BRUSH_H
#define BUBBLEGUM_TEXTURE_BRUSH_H

#include <stdint.h>
#include "bubblegum/bubblegum.h"
#include "bubblegum/brush.h"

typedef struct BUBBLEGUM_TEXTURE_BRUSH BUBBLEGUM_TEXTURE_BRUSH;

/// Creates a BUBBLEGUM_TEXTURE_BRUSH for the provided context.
BUBBLEGUM_TEXTURE_BRUSH * bg_create_texture_brush(BUBBLEGUM_CONTEXT *context);

/// Converts a BUBBLEGUM_BRUSH to a BUBBLEGUM_TEXTURE_BRUSH.
///
/// If the conversion fails (i.e., the brush is not a linear gradient), this
/// method returns NULL.
BUBBLEGUM_TEXTURE_BRUSH * bg_to_texture_brush(
	BUBBLEGUM_BRUSH *brush);

/// Converts a BUBBLEGUM_TEXTURE_BRUSH to a BUBBLEGUM_BRUSH.
BUBBLEGUM_BRUSH * bg_from_texture_brush(BUBBLEGUM_TEXTURE_BRUSH *brush);

void bg_set_texture_brush_texture(
	BUBBLEGUM_TEXTURE_BRUSH *brush,
	int width, int height,
	int row_stride,
	const uint8_t *pixels);

int bg_get_texture_brush_texture_width(BUBBLEGUM_TEXTURE_BRUSH* brush);
int bg_get_texture_brush_texture_height(BUBBLEGUM_TEXTURE_BRUSH* brush);
int bg_get_texture_brush_texture_row_stride(BUBBLEGUM_TEXTURE_BRUSH* brush);
const uint8_t * bg_get_texture_brush_texture_pixels(BUBBLEGUM_TEXTURE_BRUSH* brush);

void bg_set_texture_brush_rotation(BUBBLEGUM_TEXTURE_BRUSH* brush, float value);
float bg_get_texture_brush_rotation(BUBBLEGUM_TEXTURE_BRUSH* brush);
void bg_set_texture_brush_offset_x(BUBBLEGUM_TEXTURE_BRUSH* brush, float value);
float bg_get_texture_brush_offset_x(BUBBLEGUM_TEXTURE_BRUSH* brush);
void bg_set_texture_brush_offset_y(BUBBLEGUM_TEXTURE_BRUSH* brush, float value);
float bg_get_texture_brush_offset_y(BUBBLEGUM_TEXTURE_BRUSH* brush);
void bg_set_texture_brush_scale_x(BUBBLEGUM_TEXTURE_BRUSH* brush, float value);
float bg_get_texture_brush_scale_x(BUBBLEGUM_TEXTURE_BRUSH* brush);
void bg_set_texture_brush_scale_y(BUBBLEGUM_TEXTURE_BRUSH* brush, float value);
float bg_get_texture_brush_scale_y(BUBBLEGUM_TEXTURE_BRUSH* brush);

#endif
