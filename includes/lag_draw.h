#ifndef lag_DRAW_H
#define lag_DRAW_H

#include "lag_utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include "lag_buffer.h"

typedef enum e_lag_draw_enum {
	DEFAULT = 0,	
	FILL	= 1,
}	lag_draw_enum;

bool	lag_draw_pixel(lag_buffer *buf, uint x, uint y, char c);
bool	lag_draw_line(lag_buffer *buf, uint sx, uint sy, uint ex, uint ey, char pixel);
bool	lag_draw_rectangle(lag_buffer *buf, uint sx, uint sy, uint ex, uint ey, char pixel, lag_draw_enum flags);
// TODO draw rotate rectangle function but idk how to take points arguments

#endif
