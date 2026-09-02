#include "lag_draw.h"

bool lag_draw_rectangle(lag_buffer *buf, lag_vec2 start, lag_vec2 end, lag_pixel pixel, lag_draw_enum flags) {
	if (!buf || start.x >= (uint)buf->width || start.y >= (uint)buf->height
		|| end.x >= (uint)buf->width || end.y >= (uint)buf->height)
		return (false);

	int step_x = (start.x < end.x) ? 1 : -1;
	int step_y = (start.y < end.y) ? 1 : -1;

	if (flags & FILL) {
		for (uint y = start.y; y != end.y + step_y; y += step_y) {
			for (uint x = start.x; x != end.x + step_x; x += step_x) {
				lag_set_buffer(buf, &pixel, (lag_vec2){x, y});
			}
		}
	} else {
		for (uint x = start.x; x != end.x + step_x; x += step_x) {
			lag_set_buffer(buf, &pixel, (lag_vec2){x, start.y});
			lag_set_buffer(buf, &pixel, (lag_vec2){x, end.y});
		}
		for (uint y = start.y; y != end.y + step_y; y += step_y) {
			lag_set_buffer(buf, &pixel, (lag_vec2){start.x, y});
			lag_set_buffer(buf, &pixel, (lag_vec2){end.x, y});
		}
	}
	return (true);
}
