// BUBBLEGUM/canvas
//
// Declarations for canvas.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef BUBBLEGUM_CANVAS_H
#define BUBBLEGUM_CANVAS_H

#include "bubblegum/bubblegum.h"
#include "bubblegum/atlas.h"
#include "bubblegum/path.h"
#include "bubblegum/style.h"

typedef struct BUBBLEGUM_CANVAS BUBBLEGUM_CANVAS;

/// Creates a BUBBLEGUM_CANVAS with the specified width and height.
///
/// Width and height must be greater than zero. Values are clamped to at least 1.
///
/// Returns a valid BUBBLEGUM_CANVAS on success; otherwise, returns NULL on
/// failure.
BUBBLEGUM_API
BUBBLEGUM_API BUBBLEGUM_CANVAS * bg_create_canvas(
	BUBBLEGUM_CONTEXT *context,
	int width,
	int height);

BUBBLEGUM_API
BUBBLEGUM_API /// Resizes the BUBBLEGUM_CANVAS. Like bg_create_canvas, width and height must
/// be greater than zero. Values are clamped to at least 1.
BUBBLEGUM_API
BUBBLEGUM_API void bg_resize_canvas(BUBBLEGUM_CANVAS *canvas, int width, int height);

/// Gets the width of the canvas.
BUBBLEGUM_API
BUBBLEGUM_API int bg_get_canvas_width(BUBBLEGUM_CANVAS *canvas);

/// Gets the height of the canvas.
BUBBLEGUM_API
BUBBLEGUM_API int bg_get_canvas_height(BUBBLEGUM_CANVAS *canvas);

/// Sets the canvas position. By default, it is (0, 0).\
///
/// This only has an effect if being rendered into the backbuffer. If rendered
/// into an atlas, this value is ignored.
BUBBLEGUM_API
BUBBLEGUM_API void bg_set_canvas_position(BUBBLEGUM_CANVAS *canvas, int x, int y);

/// Gets the canvas position on the X axis.
BUBBLEGUM_API
BUBBLEGUM_API int bg_get_canvas_x(BUBBLEGUM_CANVAS *canvas);

/// Gets the canvas position on the Y axis.
BUBBLEGUM_API
BUBBLEGUM_API int bg_get_canvas_y(BUBBLEGUM_CANVAS *canvas);

/// Sets the constant integral scale.
///
/// This is multiplied by width/height when rendering the canvas to get the
/// rasterized width/height. This only has an effect when rendering into an
/// atlas.
BUBBLEGUM_API
BUBBLEGUM_API void bg_set_canvas_scale(BUBBLEGUM_CANVAS *canvas, int value);

/// Gets the constant integral scale.
BUBBLEGUM_API
BUBBLEGUM_API int bg_get_canvas_scale(BUBBLEGUM_CANVAS *canvas);

/// Begins populating a canvas.
///
/// The current contents are discarded.
BUBBLEGUM_API
BUBBLEGUM_API void bg_begin_drawing(BUBBLEGUM_CANVAS *canvas);

/// Stops drawing.
BUBBLEGUM_API
BUBBLEGUM_API void bg_end_drawing(BUBBLEGUM_CANVAS *canvas);

/// Pushes a clipping path.
BUBBLEGUM_API
BUBBLEGUM_API void bg_push_clip(BUBBLEGUM_CANVAS *canvas, BUBBLEGUM_PATH* path);

/// Pops the current clipping path.
BUBBLEGUM_API
BUBBLEGUM_API void bg_pop_clip(BUBBLEGUM_CANVAS *canvas);

/// Pushes a transform.
BUBBLEGUM_API
BUBBLEGUM_API void bg_push_transform(BUBBLEGUM_CANVAS *canvas, BUBBLEGUM_TRANSFORM* transform);

/// Pops the current transform.
BUBBLEGUM_API
BUBBLEGUM_API void bg_pop_transform(BUBBLEGUM_CANVAS *canvas);

/// Pushes a group. All children elements will be rendered as if they are a
/// single image.
///
/// For example, if the group alpha is set to 0.5, it will appear as if the
/// group as a whole is rendered at 0.5 alpha; not each element.
BUBBLEGUM_API
BUBBLEGUM_API void bg_push_group();

/// Sets the group alpha.
BUBBLEGUM_API
BUBBLEGUM_API void bg_set_group_alpha(float alpha);

/// Sets the group style.
///
/// Values in style that are unset when drawing a path will be inherited from
/// style.
BUBBLEGUM_API
BUBBLEGUM_API void bg_set_group_style(BUBBLE_STYLE *style);

/// Sets the group transform.
BUBBLEGUM_API
BUBBLEGUM_API void bg_set_group_transform(BUBBLEGUM_TRANSFORM *transform);

/// Pops the curtrent group.
BUBBLEGUM_API
BUBBLEGUM_API void bg_pop_group();

/// Draws a path.
BUBBLEGUM_API
BUBBLEGUM_API void bg_draw_path(
	BUBBLEGUM_CANVAS *canvas,
	BUBBLEGUM_PATH *path,
	BUBBLE_STYLE *style);

/// Returns true if we are currently drawing, false otherwise.
BUBBLEGUM_API
BUBBLEGUM_API bool bg_is_drawing(BUBBLEGUM_CANVAS *canvas);

/// Renders the canvas into the current backbuffer.
BUBBLEGUM_API
BUBBLEGUM_API void bg_render_canvas(BUBBLEGUM_CANVAS *canvas);

/// Renders the canvas into a BUBBLEGUM_ATLAS.
BUBBLEGUM_API
BUBBLEGUM_API BUBBLEGUM_ATLAS_SUBIMAGE* bg_render_canvas_into_atlas(
	BUBBLEGUM_CANVAS *canvas,
	BUBBLEGUM_ATLAS *atlas);

#endif
