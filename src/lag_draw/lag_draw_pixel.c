#include "lag_draw.h"

bool lag_draw_pixel(lag_buffer *buf, lag_vec2 point, lag_pixel pixel) {
	if (!buf || point.x >= (uint)buf->width || point.y >= (uint)buf->height)
		return (false);
	return (lag_set_buffer(buf, &pixel, (lag_vec2){point.x, point.y}));
}
