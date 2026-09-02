#include "lag_draw.h"

bool lag_draw_line(lag_buffer *buf, lag_vec2 start, lag_vec2 end, lag_pixel pixel) {
	int e2;
	if (!buf || start.x >= (uint)buf->width || start.y >= (uint)buf->height
		|| end.x >= (uint)buf->width || end.y >= (uint)buf->height)
		return (false);

	int x = start.x;
	int y = start.y;
	int dx = abs((int)end.x - x);
	int dy = -abs((int)end.y - y);
	int step_x = (x < (int)end.x) ? 1 : -1;
	int step_y = (y < (int)end.y) ? 1 : -1;
	int err = dx + dy;

	while (1) {
		lag_set_buffer(buf, &pixel, (lag_vec2){x, y});
		if (x == (int)end.x && y == (int)end.y)
			break;
		e2 = 2 * err;
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

bool lag_draw_line_thickness(lag_buffer *buf, lag_vec2 start, lag_vec2 end, lag_pixel pixel, uint thickness) {
	int e2;
	if (!buf || start.x >= (uint)buf->width || start.y >= (uint)buf->height
		|| end.x >= (uint)buf->width || end.y >= (uint)buf->height)
		return (false);

	int x = start.x;
	int y = start.y;
	int dx = abs((int)end.x - x);
	int dy = -abs((int)end.y - y);
	int step_x = (x < (int)end.x) ? 1 : -1;
	int step_y = (y < (int)end.y) ? 1 : -1;
	int err = dx + dy;

	while (1) {
		lag_draw_rectangle(buf, (lag_vec2){(thickness < x) ? x - thickness : 0, (thickness < y) ? y - thickness : 0}, (lag_vec2){x + thickness, y + thickness}, pixel, FILL);
		if (x == (int)end.x && y == (int)end.y)
			break;
		e2 = 2 * err;
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
