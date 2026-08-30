#ifndef LAG_DRAW_H
# define LAG_DRAW_H

# include <stdbool.h>
# include <stdlib.h>
# include "lag_buffer.h"
# include "lag_pixel.h"
# include "lag_utils.h"

typedef enum e_lag_draw_enum {
	DEFAULT		= 0,
	FILL		= 1,
} lag_draw_enum;

bool lag_draw_pixel(lag_buffer *buf, uint x, uint y, lag_pixel pixel);
bool lag_draw_line(lag_buffer *buf, uint sx, uint sy, uint ex, uint ey, lag_pixel pixel);
bool lag_draw_rectangle(lag_buffer *buf, uint sx, uint sy, uint ex, uint ey, lag_pixel pixel, lag_draw_enum flags);

#endif
