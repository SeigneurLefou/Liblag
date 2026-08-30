#include "lag_draw.h"

bool lag_draw_pixel(lag_buffer *buf, uint x, uint y, lag_pixel pixel) {
	if (!buf || x >= (uint)buf->width || y >= (uint)buf->height)
		return (false);
	return (lag_set_buffer(buf, &pixel, x, y));
}

bool lag_draw_line(lag_buffer *buf, uint sx, uint sy, uint ex, uint ey, lag_pixel pixel) {
	if (!buf || sx >= (uint)buf->width || sy >= (uint)buf->height
		|| ex >= (uint)buf->width || ey >= (uint)buf->height)
		return (false);

	int x = sx;
	int y = sy;
	int dx = abs((int)ex - x);
	int dy = -abs((int)ey - y);
	int step_x = (x < (int)ex) ? 1 : -1;
	int step_y = (y < (int)ey) ? 1 : -1;
	int err = dx + dy;

	while (1) {
		lag_set_buffer(buf, &pixel, x, y);
		if (x == (int)ex && y == (int)ey)
			break;
		int e2 = 2 * err;
		if (e2 >= dy) {
			err += dy;
			x += step_x;
		}
		if (e2 <= dx) {
			err += dx;
			y += step_y;
		}
	}
	return (true);
}

bool lag_draw_rectangle(lag_buffer *buf, uint sx, uint sy, uint ex, uint ey, lag_pixel pixel, lag_draw_enum flags) {
	if (!buf || sx >= (uint)buf->width || sy >= (uint)buf->height
		|| ex >= (uint)buf->width || ey >= (uint)buf->height)
		return (false);

	int step_x = (sx < ex) ? 1 : -1;
	int step_y = (sy < ey) ? 1 : -1;

	if (flags & FILL) {
		for (uint y = sy; y != ey + step_y; y += step_y) {
			for (uint x = sx; x != ex + step_x; x += step_x) {
				lag_set_buffer(buf, &pixel, x, y);
			}
		}
	} else {
		for (uint x = sx; x != ex + step_x; x += step_x) {
			lag_set_buffer(buf, &pixel, x, sy);
			lag_set_buffer(buf, &pixel, x, ey);
		}
		for (uint y = sy; y != ey + step_y; y += step_y) {
			lag_set_buffer(buf, &pixel, sx, y);
			lag_set_buffer(buf, &pixel, ex, y);
		}
	}
	return (true);
}
