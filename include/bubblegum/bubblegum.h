// BUBBLEGUM/bubblegum
//
// Critical declarations.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef BUBBLEGUM_BUBBLEGUM_H
#define BUBBLEGUM_BUBBLEGUM_H

#include "bubblegum/conf.h"

enum BUBBLEGUM_RENDERER
{
	BUBBLEGUM_RENDERER_NONE = 0,

#ifdef BUBBLE_ENABLE_ALLEGRO
	BUBBLEGUM_RENDERER_ALLEGRO,
#endif

#ifdef BUBBLEGUM_ENABLE_OPENGL
	BUBBLEGUM_RENDERER_OPENGL,
#endif

#ifdef BUBBLEGUM_RENDERER_DIRECTX
	BUBBLEGUM_RENDERER_DIRECTX,
#endif

	BUBBLEGUM_RENDERER_MAX
};

typedef void * (*bg_malloc_func)(size_t);
typedef void (*bg_free_func)(void *);

struct BUBBLEGUM_COLOR
{
	float r, g, b, a;
};

enum BUBBLEGUM_ERROR
{
	/// There was no error. This value is guaranteed to equal zero.
	BUBBLEGUM_ERROR_NONE = 0,

	/// Allocation failed.
	BUBBLEGUM_ERROR_OUT_OF_MEMORY,

	/// An argument was invalid.
	BUBBLEGUM_ERROR_INVALID_ARGUMENT,

	/// The method is not-yet-implemented.
	BUBBLEGUM_ERROR_NOT_YET_IMPLEMENTED
};

typedef struct BUBBLEGUM_CONTEXT BUBBLEGUM_CONTEXT;

/// Creates a BUBBLEGUM_CONTEXT using the provided allocation functions.
///
/// If the provided allocation functions are NULL, uses system defaults.
///
/// Returns the BUBBLEGUM_CONTEXT on success, or NULL on failure. Failure occurs
/// when 'alloc_func' returns NULL.
BUBBLEGUM_CONTEXT * bg_create_context(bg_malloc_func alloc_func, bg_free_func free_func);

/// Destroys the provided context.
///
/// Any objects created using this context must be destroyed prior, or they will
/// leak. Destroying objects belonging to a context after the context is an
/// error and can result in a crash.
void bg_destroy_context(BUBBLEGUM_CONTEXT *context);

/// Sets the tessellation term, or tess term.
///
/// The tessellation term describes the quality of the division of a curve. The
/// effect of the value is not generally defined, but must be greater than zero.
/// Higher values result in higher quality output.
///
/// The term parameter is clamped to at least 1.
void bg_set_context_tess_term(BUBBLEGUM_CONTEXT *context, int value);

/// Gets the tessellation term, or tess term.
///
/// See bg_set_context_tess_term for more information.
int bg_get_context_tess_term(BUBBLEGUM_CONTEXT *context);

/// Sets the renderer used by the Bubblegum context.
///
/// Renderers are enabled at library compile-time. See the BUBBLEGUM_RENDERER
/// enumeration for supported values.
void bg_set_context_renderer(BUBBLEGUM_CONTEXT *context, int value);

/// Gets the renderer used by the Bubblegum context.
int bg_get_context_renderer(BUBBLEGUM_CONTEXT *context);

/// Gets the result of the last Bubblegum function call.
///
/// Only functions that may modify state set errors. For example,
/// bg_set_context_renderer modifiers the error, but bg_get_context_renderer
/// does not.
///
/// Thus, if an error is set in bg_set_context_renderer, and then
/// bg_get_context_renderer is called, the error from bg_set_context_renderer
/// will still be returned. However, if bg_create_path was called, the error
/// will be modified (either cleared or set to a different error, whichever
/// appropriate).
///
/// In short, getters do not modify error state. Every other function does.
int bg_get_error(BUBBLEGUM_CONTEXT *context);

/// Returns bg_get_error() != BUBBLEGUM_ERROR_NONE.
bool bg_has_error(BUBBLEGUM_CONTEXT *context);

/// Sets the current Bubblegum error.
///
/// To clear an error, call bg_acknowledge_error.
///
/// Generally, this shouldn't be called...
void bg_set_error(BUBBLEGUM_CONTEXT *context, int value);

/// Acknowledges an error by clearing the error flag.
///
/// Has no effect if no error is set.
///
/// Returns the previous error.
int bg_acknowledge_error(BUBBLEGUM_CONTEXT *context);

#endif
