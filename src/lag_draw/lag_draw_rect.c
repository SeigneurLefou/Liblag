#include "lag_draw.h"

bool lag_draw_rectangle(lag_buffer *buf, lag_vec2 start, lag_vec2 end, lag_pixel *pixel, lag_draw_enum flags) {
	if (!buf)
		return false;

	int min_x = (start.x < end.x) ? start.x : end.x;
	int max_x = (start.x < end.x) ? end.x : start.x;
	int min_y = (start.y < end.y) ? start.y : end.y;
	int max_y = (start.y < end.y) ? end.y : start.y;

	if (max_x < 0 || min_x >= buf->width || max_y < 0 || min_y >= buf->height)
		return true;

	if (flags & FILL) {
		int clip_min_x = (min_x < 0) ? 0 : min_x;
		int clip_max_x = (max_x >= buf->width) ? buf->width - 1 : max_x;
		int clip_min_y = (min_y < 0) ? 0 : min_y;
		int clip_max_y = (max_y >= buf->height) ? buf->height - 1 : max_y;

		for (int y = clip_min_y; y <= clip_max_y; y++) {
			for (int x = clip_min_x; x <= clip_max_x; x++) {
				lag_set_buffer(buf, pixel, (lag_vec2){x, y});
			}
		}
	} else {
		for (int x = min_x; x <= max_x; x++) {
			lag_set_buffer(buf, pixel, (lag_vec2){x, min_y});
			lag_set_buffer(buf, pixel, (lag_vec2){x, max_y});
		}
		for (int y = min_y; y <= max_y; y++) {
			lag_set_buffer(buf, pixel, (lag_vec2){min_x, y});
			lag_set_buffer(buf, pixel, (lag_vec2){max_x, y});
		}
	}
	return true;
}
