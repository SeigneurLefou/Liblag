#ifndef lag_DRAW_H
#define lag_DRAW_H

#include "lag_buffer.h"

void lag_draw_pixel(t_buffer *buf, int x, int y, char c);
void lag_draw_line(t_buffer *buf, int sx, int sy, int ex, int ey, char ch, short color_pair);
void lag_draw_rect(t_buffer *buf, int x, int y, int w, int h, bool fill, char ch, short color_pair);
void lag_draw_sprite(t_buffer *buf, int x, int y, const char **sprite, int w, int h);
void lag_draw_text(t_buffer *buf, int x, int y, const char *text, short color_pair);

#endif
