# Bubblegum, a retained vector graphics library

... "Let us go then, you and I" ... - T. S. Eliot, *The Love Song of Alfred J
Prufrock*

Under construction.

## Example
```c
BUBBLEGUM_CONTEXT *context = bg_create_context(NULL, NULL);
bg_set_renderer(context, BUBBLEGUM_RENDERER_ALLEGRO);

BUBBLEGUM_PATH *path = bg_create_path(context);
bg_append_path_move(path, 16, 16, 0);
bg_append_path_line(path, 112, 16, 0);
bg_append_path_line(path, 112, 112, 0);
bg_append_path_line(path, 16, 122, 0);
bg_append_path_close(path);

BUBBLEGUM_STYLE *style = bg_create_style(context);
BUBBLEGUM_SOLID_BRUSH *fill = bg_create_solid_brush(context);
const BUBBLEGUM_COLOR color = { 1.0f, 0.5f, 1.0f, 1.0f };
bg_set_solid_brush_color(fill, &color);
bg_set_style_fill(context, fill);

BUBBLEGUM_CANVAS *canvas = bg_create_canvas(context, 128, 128);
bg_begin_drawing(canvas);
bg_draw_path(canvas, path, style);
bg_end_drawing(canvas);

bg_set_canvas_position(canvas, 32, 32);
bg_render_canvas(canvas);

bg_destroy_canvas(canvas);
bg_destroy_style(style);
bg_destroy_brush(bg_from_solid_brush(fill));
bg_destroy_path(path);
bg_destroy_context(context);
```

## Copyright & License

Copyright Aaron Bolyard aka [bk]door.maus

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.