#include "lag_draw.h"

bool	lag_draw_pixel(lag_buffer *buf, uint x, uint y, char pixel) {
	if (!buf || x >= buf->width || y >= buf->height)
		return (false);
	buf->content[y * buf->width + x] = pixel;
	return (true);
}

bool	lag_draw_line(lag_buffer *buf, uint sx, uint sy, uint ex, uint ey, char pixel) {
	if (!buf || sx >= buf->width || sy >= buf->height
			|| ex >= buf->width || ey >= buf->height)
		return (false);

	int x = (int)sx;
	int y = (int)sy;
	int target_x = (int)ex;
	int target_y = (int)ey;

	int dx = abs(target_x - x);
	int dy = -abs(target_y - y);
	int step_x = (x < target_x) ? 1 : -1;
	int step_y = (y < target_y) ? 1 : -1;
	int err = dx + dy;

	while (1) {
		buf->content[y * buf->width + x] = pixel;
		if (x == target_x && y == target_y)
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
