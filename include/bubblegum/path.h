// BUBBLEGUM/path
//
// Declarations for paths.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright [bk]door.maus

#ifndef BUBBLEGUM_PATH_H
#define BUBBLEGUM_PATH_H

typedef struct BUBBLEGUM_PATH BUBBLEGUM_PATH;

/// Creates a BUBBLEGUM_PATH for the provided context.
///
/// Returns the BUBBLEGUM_PATH on success, or NULL on failure. To see why the
BUBBLEGUM_API
BUBBLEGUM_API /// function failed, call bg_get_error.
BUBBLEGUM_API
BUBBLEGUM_API BUBBLEGUM_PATH * bg_create_path(BUBBLEGUM_CONTEXT *context);

/// Destroys the path.
BUBBLEGUM_API
BUBBLEGUM_API void bg_destroy_path(BUBBLEGUM_PATH *path);

enum BUBBLEGUM_COMMAND_FLAGS
{
	/// The command is absolute; the previous commands do not matter.
	///
	/// This is guaranteed to always be zero.
	BUBBLEGUM_COMMAND_FLAG_ABSOLUTE = 0,
	
	/// The command is relative to the previous command.
	BUBBLEGUM_COMMAND_FLAG_RELATIVE = 1 << 0,
};

BUBBLEGUM_API
BUBBLEGUM_API void bg_append_path_move(BUBBLEGUM_PATH *path, float x, float y, int flags);
BUBBLEGUM_API
BUBBLEGUM_API void bg_append_path_line(BUBBLEGUM_PATH *path, float x, float y, int flags);
BUBBLEGUM_API
BUBBLEGUM_API void bg_append_path_quadratic_curve(
	BUBBLEGUM_PATH *path,
	float anchor_x, float anchor_y,
	float x, float y,
	int flags);
BUBBLEGUM_API
BUBBLEGUM_API void bg_append_path_cubic_curve(
	BUBBLEGUM_PATH *path,
	float anchor1_x, anchor1_y,
	float anchor2_x, anchor2_y,
	float x, float y,
	int flags);
BUBBLEGUM_API
BUBBLEGUM_API void bg_append_path_close(
	BUBBLEGUM_PATH *path,
	int flags);
BUBBLEGUM_API
BUBBLEGUM_API void bg_insert_path_move(BUBBLEGUM_PATH *path, int index, float x, float y, int flags);
BUBBLEGUM_API
BUBBLEGUM_API void bg_insert_path_line(BUBBLEGUM_PATH *path, int index, float x, float y, int flags);
BUBBLEGUM_API
BUBBLEGUM_API void bg_insert_path_quadratic_curve(
	BUBBLEGUM_PATH *path,
	int index,
	float anchor_x, float anchor_y,
	float x, float y,
	int flags);
BUBBLEGUM_API
BUBBLEGUM_API void bg_insert_path_cubic_curve(
	BUBBLEGUM_PATH *path,
	int index,
	float anchor1_x, anchor1_y,
	float anchor2_x, anchor2_y,
	float x, float y,
	int flags);
BUBBLEGUM_API
BUBBLEGUM_API void bg_insert_path_close(
	BUBBLEGUM_PATH *path,
	int index,
	int flags);
BUBBLEGUM_API
BUBBLEGUM_API void bg_clear_path(BUBBLEGUM_PATH *path);
BUBBLEGUM_API
BUBBLEGUM_API void bg_remove_path_command(BUBBLEGUM_PATH *path, int index);

enum BUBBLEGUM_COMMAND_TYPE
{
	BUBBLEGUM_COMMAND_TYPE_NONE = 0,
	BUBBLEGUM_COMMAND_TYPE_MOVE,
	BUBBLEGUM_COMMAND_TYPE_LINE,
	BUBBLEGUM_COMMAND_TYPE_QUADRATIC_CURVE,
	BUBBLEGUM_COMMAND_TYPE_CUBIC_CURVE,
	BUBBLEGUM_COMMAND_TYPE_CLOSE,
	BUBBLEGUM_COMMAND_TYPE_MAX
};

BUBBLEGUM_API
BUBBLEGUM_API int bg_get_num_path_commands(BUBBLEGUM_PATH *path);
BUBBLEGUM_API
BUBBLEGUM_API int bg_get_path_command_type(BUBBLEGUM_PATH *path, int command_index);
BUBBLEGUM_API
BUBBLEGUM_API float bg_get_path_command_x(BUBBLEGUM_PATH *path, int command_index, int x_index);
BUBBLEGUM_API
BUBBLEGUM_API float bg_get_path_command_y(BUBBLEGUM_PATH *path, int command_index, int y_index);
BUBBLEGUM_API
BUBBLEGUM_API int bg_get_path_command_flags(BUBBLEGUM_PATH *path, int command_index);

#endif
