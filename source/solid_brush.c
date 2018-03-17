// BUBBLEGUM/solid_brush
//
// Definitions for solid brush.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <assert>
#include "brush.h"
#include "bubblegum/brush.h"
#include "bubblegum/bubblegum.h"
#include "bubblegum/solid_brush.h"

BUBBLEGUM_API BUBBLEGUM_SOLID_BRUSH *
bg_create_solid_brush(BUBBLEGUM_CONTEXT *context)
{
	assert(context != NULL && "context is null");

	if (context == NULL)
	{
		return NULL;
	}

	bg_acknowledge_error(context);

	BUBBLEGUM_SOLID_BRUSH *result = context->alloc(sizeof(BUBBLEGUM_SOLID_BRUSH));
	if (result == NULL)
	{
		bg_set_error(context, BUBBLEGUM_ERROR_OUT_OF_MEMORY);
		return NULL;
	}

	if (!bg_create_brush(&result->brush, context, BUBBLEGUM_BRUSH_TYPE_SOLID))
	{
		context->free(result);
		return NULL;
	}

	result->color.r = 1.0f;
	result->color.g = 1.0f;
	result->color.b = 1.0f;
	result->color.a = 1.0f;

	return result;
}

BUBBLEGUM_API BUBBLEGUM_SOLID_BRUSH *
bg_to_solid_brush(BUBBLEGUM_BRUSH *brush)
{
	assert(brush != NULL && "brush is null");

	if (brush == NULL || brush->type != BUBBLEGUM_BRUSH_TYPE_SOLID)
	{
		return NULL;
	}

	return (BUBBLEGUM_SOLID_BRUSH *)brush;
}

BUBBLEGUM_API BUBBLEGUM_BRUSH *
bg_from_solid_brush(BUBBLEGUM_SOLID_BRUSH *brush)
{
	return (BUBBLEGUM_BRUSH *)brush;
}

BUBBLEGUM_API void
bg_set_solid_brush_color(
	BUBBLEGUM_SOLID_BRUSH *brush,
	const BUBBLEGUM_SOLID_BRUSH *color)
{
	assert(brush != NULL && "brush is null");
	assert(color != NULL && "color is null");

	if (brush != NULL && color != NULL)
	{
		brush->color = *color;
	}
}

BUBBLEGUM_API BUBBLEGUM_COLOR
bg_get_solid_brush_color(BUBBLEGUM_SOLID_BRUSH *brush)
{
	assert(brush != NULL && "brush is null");

	if (brush == NULL)
	{
		static const BUBBLEGUM_COLOR WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
		return WHITE;
	}

	return brush->color;
}
