// BUBBLEGUM/internal/path
//
// Internal declarations for path.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef BUBBLEGUM_INTERNAL_PATH_H
#define BUBBLEGUM_INTERNAL_PATH_H

#include "bubblegum/bubblegum.h"
#include "bubblegum/path.h"

#define BUBBLEGUM_PATH_COMMAND_MAX_ARGS 3
struct BUBBLEGUM_PATH_COMMAND
{
	// Corresponds to BUBBLEGUM_COMMAND_TYPE
	int type;

	// Corresponds to BUBBLEGUM_COMMAND_FLAGS
	int flags;

	int arguments_length;
	float x[BUBBLEGUM_PATH_COMMAND_MAX_ARGS];
	float y[BUBBLEGUM_PATH_COMMAND_MAX_ARGS];

	float absolute_x;
	float absolute_y;
};

#define BUBBLEGUM_PATH_COMMAND_INITIAL_CAPACITY 32

struct BUBBLEGUM_PATH
{
	BUBBLEGUM_CONTEXT *context;

	int commands_capacity;
	int commands_length;
	BUBBLEGUM_PATH_COMMAND *commands;
};

bool bg_resize_path_commands(BUBBLEGUM_PATH *path, int new_capacity);
bool bg_insert_path_command(
	BUBBLEGUM_PATH *path,
	int index,
	const BUBBLEGUM_PATH_COMMAND *command);

#endif
