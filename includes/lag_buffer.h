#ifndef LAG_BUFFER_H
#define LAG_BUFFER_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lag_pixel.h"
#include "lag_utils.h"

typedef struct s_lag_buffer {
	int			width;
	int			height;
	lag_pixel	*content;
}	lag_buffer;

bool		lag_create_buffer(lag_buffer *buffer, int w, int h);
bool		lag_destroy_buffer(lag_buffer *buf);
bool		lag_clear_buffer(lag_buffer *buf);
bool		lag_fill_buffer(lag_buffer *buf, lag_pixel *pixel);
lag_pixel	lag_get_buffer(lag_buffer *buf, uint x, uint y);
bool		lag_set_buffer(lag_buffer *buf, lag_pixel *pixel, uint x, uint y);
bool		lag_blit_buffer(lag_buffer *src, lag_buffer *dest, uint sx, uint sy);

#endif
