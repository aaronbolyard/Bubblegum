// BUBBLEGUM/path
//
// Definitions for path.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bubblegum/bubblegum.h"
#include "bubblegum/path.h"
#include "internal/context.h"
#include "internal/path.h"

bool
bg_resize_path_commands(BUBBLEGUM_PATH *path, int new_capacity)
{
	assert(path != NULL && "path is NULL");
	assert(path->context != NULL && "path->context is NULL");
	assert(new_capacity >= 0 && "new_capacity is less than zero");

	// The array never shrinks.
	if (new_capacity < path->commands_capacity)
	{
		return true;
	}

	size_t old_commands_size =
		path->commands_length * sizeof(BUBBLEGUM_PATH_COMMAND);
	size_t new_commands_size =
		new_capacity * sizeof(BUBBLEGUM_PATH_COMMAND);
	BUBBLEGUM_PATH_COMMAND *new_commands =
		(BUBBLEGUM_PATH_COMMAND *)path->context->alloc(new_commands_size);

	if (new_commands == NULL)
	{
		path->context->error_code = BUBBLEGUM_ERROR_OUT_OF_MEMORY;
		return false;
	}
	else
	{
		// Copy old command data.
		memcpy(new_commands, path->commands, old_commands_size);

		// Free old command data.
		path->context->free(path->commands);

		// Update path with new command data.
		path->commands_capacity = new_capacity;
		path->commands = new_commands;

		return true;
	}
}

bool
bg_insert_path_command(
	BUBBLEGUM_PATH *path,
	int index,
	const BUBBLEGUM_PATH_COMMAND* command)
{
	assert(path != NULL && "path is NULL");
	assert(index >= 0 && "index is less than zero");
	assert(index < path->commands_length && "index is out of bounds");

	if (index > path->commands_length)
	{
		index = path->commands_length;
	}
	else if (index < 0)
	{
		index = 0;
	}

	int new_length = path->commands_length + 1;
	if (new_length > path->commands_capacity)
	{
		// Since we only increment one at a time, doubling capacity will always
		// ensure there is enough room for the new command.
		if (!bg_resize_path_commands(path, path->commands_capacity * 2))
		{
			return false;
		}
	}

	if (index == path->commands_length)
	{
		// Simple append. Just copy to the end of the array.
		memcpy(path->commands + index, command, sizeof(BUBBLEGUM_PATH_COMMAND));
	}
	else
	{
		int remainder = path->commands_length - index;

		// Shift commands.
		memmove(
			path->commands + index + 1,
			path->commands + index,
			remainder * sizeof(BUBBLEGUM_PATH_COMMAND));

		// Insert new command.
		memcpy(path->commands + index, command, sizeof(BUBBLEGUM_PATH_COMMAND));
	}

	path->commands_length = new_length;

	return true;
}

void
bg_remove_path_command(BUBBLEGUM_PATH *path, int index)
{
	assert(path != NULL && "path is NULL");
	assert(index >= 0 && "index is less than zero");
	assert(index < path->commands_length && "index is out of bounds");

	if (path == NULL)
	{
		return;
	}

	bg_acknowledge_error(path->context);

	if (index < 0)
	{
		index = 0;
	}
	else if (index >= path->commands_length)
	{
		index = path->commands_length - 1;
	}

	// There's nothing to remove.
	if (path->commands_length == 0)
	{
		return;
	}

	if (index == path->commands_length)
	{
		--path->commands_length;
	}
	else
	{
		int remainder = path->commands_length - index;

		// Shift commands.
		memmove(
			path->commands + index,
			path->commands + index + 1,
			remainder * sizeof(BUBBLEGUM_PATH_COMMAND));

		--path->commands_length;
	}
}

BUBBLEGUM_PATH *
bg_create_path(BUBBLEGUM_CONTEXT *context)
{
	assert(context != NULL && "context is null");
	bg_acknowledge_error(context);

	BUBBLEGUM_PATH *result = context->alloc(sizeof(BUBBLEGUM_PATH));
	if (result == NULL)
	{
		context->error_code = BUBBLEGUM_ERROR_OUT_OF_MEMORY;
		return NULL;
	}

	result->context = context;
	result->commands_capacity = BUBBLEGUM_PATH_COMMAND_INITIAL_CAPACITY;
	result->commands_length = 0;

	size_t commands_size =
		sizeof(BUBBLEGUM_PATH_COMMAND) *
		BUBBLEGUM_PATH_COMMAND_INITIAL_CAPACITY;
	result->commands = (BUBBLEGUM_PATH_COMMAND *)context->alloc(commands_size);
	if (result->commands == NULL)
	{
		context->free(result);
		context->error_code = BUBBLEGUM_ERROR_OUT_OF_MEMORY;
		return NULL;
	}

	return result;
}

void
bg_destroy_path(BUBBLEGUM_PATH *path)
{
	if (path != NULL)
	{
		path->context->free(path->commands);
		path->context->free(path);
	}
}

void
bg_append_path_move(BUBBLEGUM_PATH *path, float x, float y, int flags)
{
	assert(path != NULL && "path is NULL");

	if (path == NULL)
	{
		return;
	}

	bg_insert_path_move(path, path->commands_length, x, y, flags);
}

void
bg_append_path_line(BUBBLEGUM_PATH *path, float x, float y, int flags)
{
	assert(path != NULL && "path is NULL");

	if (path == NULL)
	{
		return;
	}

	bg_insert_path_line(path, path->commands_length, x, y, flags);
}

void
bg_append_path_quadratic_curve(
	BUBBLEGUM_PATH *path,
	float anchor_x, float anchor_y
	float x, float y,
	int flags)
{
	assert(path != NULL && "path is NULL");

	if (path == NULL)
	{
		return;
	}

	bg_insert_path_quadratic_curve(
		path,
		path->commands_length,
		anchor_x, anchor_y,
		x, y,
		flags);
}

void
bg_append_path_cubic_curve(
	BUBBLEGUM_PATH *path,
	float anchor1_x, float anchor1_y
	float anchor2_x, float anchor2_y
	float x, float y,
	int flags)
{
	assert(path != NULL && "path is NULL");

	if (path == NULL)
	{
		return;
	}

	bg_insert_path_cubic_curve(
		path,
		path->commands_length,
		anchor1_x, anchor1_y,
		anchor2_x, anchor2_y,
		x, y,
		flags);
}

void
bg_append_path_close(BUBBLEGUM_PATH *path, int flags)
{
	assert(path != NULL && "path is NULL");

	if (path == NULL)
	{
		return;
	}

	bg_insert_path_close(path, path->commands_length, flags);
}

void
bg_insert_path_move(BUBBLEGUM_PATH *path, int index, float x, float y, int flags)
{
	assert(path != NULL && "path is NULL");

	if (path == NULL)
	{
		return;
	}
	bg_acknowledge_error(path->context);

	BUBBLEGUM_PATH_COMMAND command;
	command.type = BUBBLE_COMMAND_TYPE_MOVE;
	command.flags = flags;
	command.arguments_length = 1;
	command.x[0] = x;
	command.y[0] = y;

	if (!(flags & BUBBLEGUM_COMMAND_FLAG_RELATIVE) ||
	    path->commands_length == 0)
	{
		command.absolute_x = x;
		command.absolute_y = y;
	}
	else
	{
		command.absolute_x =
			 x + path->commands[paths->commands_length - 1].absolute_x;
		command.absolute_y =
			 y + path->commands[paths->commands_length - 1].absolute_y;
	}

	bg_insert_path_command(path, index, &command);
}

void
bg_insert_path_line(BUBBLEGUM_PATH *path, float x, float y, int flags)
{
	assert(path != NULL && "path is NULL");

	if (path == NULL)
	{
		return;
	}
	bg_acknowledge_error(path->context);

	BUBBLEGUM_PATH_COMMAND command;
	command.type = BUBBLE_COMMAND_TYPE_LINE;
	command.flags = flags;
	command.arguments_length = 1;
	command.x[0] = x;
	command.y[0] = y;

	if (!(flags & BUBBLEGUM_COMMAND_FLAG_RELATIVE) ||
	    path->commands_length == 0)
	{
		command.absolute_x = x;
		command.absolute_y = y;
	}
	else
	{
		command.absolute_x =
			 x + path->commands[paths->commands_length - 1].absolute_x;
		command.absolute_y =
			 y + path->commands[paths->commands_length - 1].absolute_y;
	}

	bg_insert_path_command(path, index, &command);
}

void
bg_insert_path_quadratic_curve(
	BUBBLEGUM_PATH *path,
	float anchor_x, float anchor_y,
	float x, float y,
	int flags)
{
	assert(path != NULL && "path is NULL");

	if (path == NULL)
	{
		return;
	}
	bg_acknowledge_error(path->context);

	BUBBLEGUM_PATH_COMMAND command;
	command.type = BUBBLE_COMMAND_TYPE_QUADRATIC_CURVE;
	command.flags = flags;
	command.arguments_length = 2;
	command.x[0] = anchor_x;
	command.y[0] = anchor_y;
	command.x[1] = x;
	command.y[1] = y;

	if (!(flags & BUBBLEGUM_COMMAND_FLAG_RELATIVE) ||
	    path->commands_length == 0)
	{
		command.absolute_x = x;
		command.absolute_y = y;
	}
	else
	{
		command.absolute_x =
			 x + path->commands[paths->commands_length - 1].absolute_x;
		command.absolute_y =
			 y + path->commands[paths->commands_length - 1].absolute_y;
	}

	bg_insert_path_command(path, index, &command);
}

void
bg_insert_path_cubic_curve(
	BUBBLEGUM_PATH *path,
	float anchor1_x, float anchor1_y,
	float anchor2_x, float anchor2_y,
	float x, float y,
	int flags)
{
	assert(path != NULL && "path is NULL");

	if (path == NULL)
	{
		return;
	}
	bg_acknowledge_error(path->context);

	BUBBLEGUM_PATH_COMMAND command;
	command.type = BUBBLE_COMMAND_TYPE_CUBIC_CURVE;
	command.flags = flags;
	command.arguments_length = 3;
	command.x[0] = anchor1_x;
	command.y[0] = anchor1_y;
	command.x[1] = anchor2_x;
	command.y[1] = anchor2_y;
	command.x[2] = x;
	command.y[2] = y;

	if (!(flags & BUBBLEGUM_COMMAND_FLAG_RELATIVE) ||
	    path->commands_length == 0)
	{
		command.absolute_x = x;
		command.absolute_y = y;
	}
	else
	{
		command.absolute_x =
			 x + path->commands[paths->commands_length - 1].absolute_x;
		command.absolute_y =
			 y + path->commands[paths->commands_length - 1].absolute_y;
	}

	bg_insert_path_command(path, index, &command);
}

void
bg_insert_path_close(
	BUBBLEGUM_PATH *path,
	int index,
	int flags)
{
	assert(path != NULL && "path is NULL");

	if (path == NULL)
	{
		return;
	}
	bg_acknowledge_error(path->context);

	// Close is always absolute.
	flags &= ~(BUBBLEGUM_COMMAND_FLAG_RELATIVE);

	if (index >= path->commands_length)
	{
		index = path->commands_length;
	}

	// Find previous move or close command. Failing that, use the first command.
	int previous_start_command = index;
	while (previous_start_command > 0)
	{
		if (path->commands[previous_start_command] == BUBBLEGUM_COMMAND_TYPE_MOVE ||
		    path->commands[previous_start_command] == BUBBLEGUM_COMMAND_TYPE_CLOSE)
		{
			break;
		}

		--previous_start_command;
	}

	BUBBLEGUM_PATH_COMMAND command;
	command.type = BUBBLE_COMMAND_TYPE_CLOSE;
	command.flags = flags;
	command.arguments_length = 1;

	if (previous_start_command < path->commands_length)
	{
		command.x[0] = path->commands[previous_start_command].absolute_x;
		command.y[0] = path->commands[previous_start_command].absolute_y;
	}
	else
	{
		command.x[0] = 0.0f;
		command.y[0] = 0.0f;
	}

	command.absolute_x = command.x[0];
	command.absolute_y = command.y[0];

	bg_insert_path_command(path, index, &command);
}

void
bg_clear_path(BUBBLEGUM_PATH *path)
{
	assert(path != NULL && "path is NULL");
	bg_acknowledge_error(path->context);

	if (path != NULL)
	{
		path->commands_length = 0;
	}
}

int
bg_get_num_path_commands(BUBBLEGUM_PATH *path)
{
	assert(path != NULL && "path is NULL");

	return path->commands_length;
}

int
bg_get_path_command_type(BUBBLEGUM_PATH *path, int command_index)
{
	assert(path != NULL && "path is NULL");
	assert(command_index >= 0 && "index is less than zero");
	assert(command_index < path->commands_length && "index is out of bounds");

	if (path != NULL)
	{
		if (command_index >= 0 && command_index < path->commands_length)
		{
			return path->commands[command_index].type;
		}
	}

	return BUBBLE_COMMAND_TYPE_NONE;
}

float
bg_get_path_command_x(BUBBLEGUM_PATH *path, int command_index, int x_index)
{
	assert(path != NULL && "path is NULL");
	assert(command_index >= 0 && "index is less than zero");
	assert(command_index < path->commands_length && "index is out of bounds");

	if (path != NULL)
	{
		if (command_index >= 0 && command_index < path->commands_length)
		{
			if (x_index < path->commands[command_index].arguments_length)
			{
				return path->commands[command_index].x[x_index];
			}
		}
	}

#ifdef NAN
	return NAN;
#else
	return FLT_MAX;
#endif
}

float
bg_get_path_command_y(BUBBLEGUM_PATH *path, int command_index, int y_index)
{
	assert(path != NULL && "path is NULL");
	assert(command_index >= 0 && "index is less than zero");
	assert(command_index < path->commands_length && "index is out of bounds");

	if (path != NULL)
	{
		if (command_index >= 0 && command_index < path->commands_length)
		{
			if (y_index < path->commands[command_index].arguments_length)
			{
				return path->commands[command_index].y[y_index];
			}
		}
	}

#ifdef NAN
	return NAN;
#else
	return FLT_MAX;
#endif
}

int
bg_get_path_command_flags(BUBBLEGUM_PATH *path, int command_index)
{
	assert(path != NULL && "path is NULL");
	assert(command_index >= 0 && "index is less than zero");
	assert(command_index < path->commands_length && "index is out of bounds");

	if (path != NULL)
	{
		if (command_index >= 0 && command_index < path->commands_length)
		{
			return path->commands[command_index].flags;
		}
	}

	return BUBBLE_COMMAND_TYPE_NONE;
}
