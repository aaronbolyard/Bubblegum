// BUBBLEGUM/brush
//
// Declarations common to brushes.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef BUBBLEGUM_BRUSH_H
#define BUBBLEGUM_BRUSH_H

typedef struct BUBBLEGUM_BRUSH BUBBLEGUM_BRUSH;

enum BUBBLEGUM_BRUSH_TYPE
{
	/// Specifies an invalid or non-existent brush.
	BUBBLEGUM_BRUSH_TYPE_NONE = 0,

	/// Specifies a solid brush (BUBBLEGUM_SOLID_BRUSH).
	BUBBLEGUM_BRUSH_TYPE_SOLID,

	/// Specifies a linear gradient brush (BUBBLEGUM_LINEAR_GRADIENT_BRUSH).
	BUBBLEGUM_BRUSH_TYPE_LINEAR_GRADIENT,

	/// Specifies a radial gradient brush (BUBBLEGUM_RADIAL_GRADIENT_BRUSH).
	BUBBLEGUM_BRUSH_TYPE_RADIAL_GRADIENT,

	/// Specifies a texture brush (BUBBLEGUM_TEXTURE_BRUSH).
	BUBBLEGUM_BRUSH_TYPE_TEXTURE,

	/// Specifies a pattern brush (BUBBLEGUM_PATTERN_BRUSH).
	BUBBLEGUM_BRUSH_TYPE_PATTERN
};

/// Gets the BUBBLEGUM_BRUSH_TYPE of the provided brush.
BUBBLEGUM_API
BUBBLEGUM_API int bg_get_brush_type(BUBBLEGUM_BRUSH *brush);

/// Destroys a brush.
BUBBLEGUM_API
BUBBLEGUM_API void bg_destroy_brush(BUBBLEGUM_BRUSH *brush);

#endif
