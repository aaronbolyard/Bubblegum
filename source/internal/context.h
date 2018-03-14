// BUBBLEGUM/internal/context
//
// Declarations for context.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef BUBBLEGUM_INTERNAL_CONTEXT_H
#define BUBBLEGUM_INTERNAL_CONTEXT_H

#include "bubblegum/bubblegum.h"

struct BUBBLEGUM_CONTEXT
{
	bg_malloc_func alloc;
	bg_free_func free;

	int error_code;
	int renderer;

	int tess_term;
};

void* bg_malloc(size_t size);
void bg_free(void* pointer);

#endif
