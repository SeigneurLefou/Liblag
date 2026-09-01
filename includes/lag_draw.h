#ifndef LAG_DRAW_H
# define LAG_DRAW_H

# include <stdbool.h>
# include <stdlib.h>
# include "lag_buffer.h"
# include "lag_pixel.h"
# include "lag_utils.h"
# include "lag_vec2.h"

typedef enum e_lag_draw_enum {
	DEFAULT		= 0,
	FILL		= 1,
} lag_draw_enum;

bool lag_draw_pixel(lag_buffer *buf, lag_vec2 point, lag_pixel pixel);
bool lag_draw_line(lag_buffer *buf, lag_vec2 start, lag_vec2 end, lag_pixel pixel);
bool lag_draw_rectangle(lag_buffer *buf, lag_vec2 start, lag_vec2 end, lag_pixel pixel, lag_draw_enum flags);

#endif
