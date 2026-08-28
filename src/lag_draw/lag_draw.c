#include "lag_draw.h"

bool	lag_draw_pixel(lag_buffer *buf, uint x, uint y, char pixel) {
	if (x >= buf->width || y >= buf->height)
		return (false);
	buf->content[y * buf->width + x] = pixel;
	return (true);
}
