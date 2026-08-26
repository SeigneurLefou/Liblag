#ifndef ALG_DRAW_H
#define ALG_DRAW_H

#include "alg_buffer.h"

void alg_draw_pixel(t_buffer *buf, int x, int y, char c);
void alg_draw_line(t_buffer *buf, int sx, int sy, int ex, int ey, char ch, short color_pair);
void alg_draw_rect(t_buffer *buf, int x, int y, int w, int h, bool fill, char ch, short color_pair);
void alg_draw_sprite(t_buffer *buf, int x, int y, const char **sprite, int w, int h);
void alg_draw_text(t_buffer *buf, int x, int y, const char *text, short color_pair);

#endif
