#include "lag_draw.h"

bool	lag_draw_pixel(lag_buffer *buf, uint x, uint y, char pixel) {
	if (!buf || x >= buf->width || y >= buf->height)
		return (false);
	lag_set_buffer(buf, pixel, x, y);
	return (true);
}

bool	lag_draw_line(lag_buffer *buf, uint sx, uint sy, uint ex, uint ey, char pixel) {
	if (!buf || sx >= buf->width || sy >= buf->height
			|| ex >= buf->width || ey >= buf->height)
		return (false);

	uint	x = sx;
	uint	y = sy;

	int		dx = abs(ex - x);
	int		dy = -abs(ey - y);
	int		step_x = (x < ex) ? 1 : -1;
	int		step_y = (y < ey) ? 1 : -1;
	int		err = dx + dy;

	while (1) {
		lag_set_buffer(buf, pixel, x, y);
		if (x == ex && y == ey)
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

bool	lag_draw_rectangle(lag_buffer *buf, uint sx, uint sy, uint ex, uint ey, char pixel, lag_draw_enum flags) {
	if (!buf || sx >= buf->width || sy >= buf->height
			|| ex >= buf->width || ey >= buf->height)
		return (false);

	uint	x = sx;
	uint	y = sy;
	int		step_x = (x < ex) ? 1 : -1;
	int		step_y = (y < ey) ? 1 : -1;

	if (flags & FILL) {
		while (y != ey) {
			x = (int)sx;
			while (x != ex) {
				lag_set_buffer(buf, pixel, x, y);
				x += step_x;
			}
			y += step_y;
		}
	} else {
		buf->content[sy * buf->width + x] = pixel;
		buf->content[ey * buf->width + x] = pixel;
		buf->content[y * buf->width + sx] = pixel;
		buf->content[y * buf->width + ex] = pixel;
		while (x != ex) {
			x += step_x;
			buf->content[sy * buf->width + x] = pixel;
			buf->content[ey * buf->width + x] = pixel;
		}
		while (y != ey) {
			y += step_y;
			buf->content[y * buf->width + sx] = pixel;
			buf->content[y * buf->width + ex] = pixel;
		}
	}
	return (true);
}
