// BUBBLEGUM/context
//
// Definitions for context.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <assert.h>
#include <stdlib.h>
#include "bubblegum/bubblegum.h"
#include "internal/context.h"

void*
bg_malloc(size_t size)
{
	return malloc(size);
}

void
bg_free(void* pointer)
{
	free(pointer);
}

BUBBLEGUM_CONTEXT *
bg_create_context(bg_malloc_func alloc_func, bg_free_func free_func)
{
	BUBBLEGUM_CONTEXT *context = NULL;

	if (alloc_func == NULL || free_func == NULL)
	{
		alloc_func = &bg_malloc;
		free_func = &bg_free;
	}

	context = (BUBBLEGUM_CONTEXT *)alloc_func(sizeof(BUBBLEGUM_CONTEXT));
	if (context == NULL)
	{
		return NULL;
	}

	// Set state.
	context->alloc = alloc_func;
	context->free = free_func;
	context->error_code = BUBBLEGUM_ERROR_NONE;
	context->renderer = BUBBLEGUM_RENDERER_NONE;

	// Set parameters.
	//
	// Parameters are values that affect rendering. These are configurable by
	// editing bubblegum/conf.h when building Bubblegum.
	context->tess_term = BUBBLEGUM_DEFAULT_TESS_TERM;

	return context;
}

void
bg_destroy_context(BUBBLEGUM_CONTEXT *context)
{
	if (context != NULL)
	{
		context->free(context);
	}
}

void
bg_set_context_tess_term(BUBBLEGUM_CONTEXT *context, int value)
{
	assert(context != NULL && "bubblegum context is null");
	bg_acknowledge_error(context);

	if (context != NULL)
	{
		if (value < 1)
		{
			value = 1;
			context->error_code = BUBBLEGUM_ERROR_INVALID_ARGUMENT;
		}

		context->tess_term = value;
	}
}

int
bg_get_context_tess_term(BUBBLEGUM_CONTEXT *context, int value)
{
	assert(context != NULL && "bubblegum context is null");
	assert(context->tess_term >= 1 && "bubblegum tess term is bad");

	if (context != NULL)
	{
		return context->tess_term;
	}

	return 0;
}

void
bg_set_context_renderer(BUBBLEGUM_CONTEXT *context, int value)
{
	assert(context != NULL && "bubblegum context is null");
	bg_acknowledge_error(context);

	if (context != NULL)
	{
		if (value >= BUBBLEGUM_RENDERER_NONE && value < BUBBLEGUM_RENDERER_MAX)
		{
			context->renderer = value;
		}
		else
		{
			context->error_code = BUBBLEGUM_ERROR_INVALID_ARGUMENT;
		}
	}
}

int
bg_get_context_renderer(BUBBLEGUM_CONTEXT *context)
{
	assert(context != NULL && "bubblegum context is null");
	assert(context->renderer >= BUBBLEGUM_RENDERER_NONE && "renderer is bad");
	assert(context->renderer < BUBBLEGUM_RENDERER_MAX && "renderer is bad");

	if (context != NULL)
	{
		return context->renderer;
	}

	return BUBBLEGUM_RENDERER_NONE;
}

int
bg_get_error(BUBBLEGUM_CONTEXT *context)
{
	assert(context != NULL && "bubblegum context is null");

	if (context != NULL)
	{
		return context->error_code;
	}

	return BUBBLEGUM_ERROR_INVALID_ARGUMENT;
}

bool
bg_has_error(BUBBLEGUM_CONTEXT *context)
{
	assert(context != NULL && "bubblegum context is null");

	if (context != NULL)
	{
		return context->error_code != BUBBLEGUM_RENDERER_NONE;
	}

	return true;
}

void
bg_set_error(BUBBLEGUM_CONTEXT *context, int value)
{
	assert(context != NULL && "bubblegum context is null");

	if (context != NULL)
	{
		context->error_code = value;
	}
}

int
bg_acknowledge_error(BUBBLEGUM_CONTEXT *context)
{
	assert(context != NULL && "bubblegum context is null");

	if (context != NULL)
	{
		int previous_error_code = context->error_code;
		context->error_code = BUBBLEGUM_ERROR_NONE;

		return previous_error_code;
	}
	else
	{
		return BUBBLEGUM_ERROR_INVALID_ARGUMENT;
	}
}
