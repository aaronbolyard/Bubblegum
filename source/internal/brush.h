// BUBBLEGUM/internal/brush
//
// Internal declarations for brush.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef BUBBLEGUM_INTERNAL_BRUSH_H
#define BUBBLEGUM_INTERNAL_BRUSH_H

typedef void (*bg_brush_destructor)(BUBBLEGUM_BRUSH *brush);

struct BUBBLEGUM_BRUSH
{
	BUBBLEGUM_CONTEXT *context;

	// Corresponds to BUBBLEGUM_BRUSH_TYPE enumeration.
	int type;

	// If not NULL, called when brush is destroyed.
	bg_brush_destructor destructor;
};

bool bg_create_brush(
	BUBBLEGUM_BRUSH *brush,
	BUBBLEGUM_CONTEXT *context,
	int type);

#endif