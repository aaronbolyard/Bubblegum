// BUBBLEGUM/internal/brush
//
// Definitions for brush.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <assert.h>
#include "bubblegum/brush.h"
#include "bubblegum/bubblegum.h"
#include "internal/brush.h"

int
bg_get_brush_type(BUBBLEGUM_BRUSH *brush)
{
	assert(brush != NULL && "brush is null");

	if (brush == NULL)
	{
		return BUBBLEGUM_BRUSH_TYPE_NONE;
	}

	return brush->type;
}

void
bg_destroy_brush(BUBBLEGUM_BRUSH *brush)
{
	if (brush->destructor != NULL)
	{
		brush->destructor(brush);
	}

	brush->context->free(brush);
}

bool
bg_create_brush(BUBBLEGUM_BRUSH *brush, BUBBLEGUM_CONTEXT *context, int type)
{
	assert(brush != NULL && "brush is null");
	assert(context != NULL && "context is null");

	if (brush == NULL || context == NULL)
	{
		return false;
	}

	brush->context = context;
	brush->type = type;
	brush->destructor = NULL;

	return true;
}
