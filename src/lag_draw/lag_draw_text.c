#include "lag_draw.h"

bool lag_draw_text(lag_buffer *buf, lag_vec2 start, char *str, lag_color *fg, lag_color *bg) {
	if (!buf || !str || !fg || !bg) return false;

	for (int i = 0; str[i]; i++) {
		lag_pixel	px;
		if (start.x + i >= buf->width)
			break;
		char	c[2] = {str[i], '\0'};
		if (!lag_set_pixel(&px, c, fg, bg)) return false;
		lag_set_buffer(buf, &px, (lag_vec2){i + start.x, start.y});
	}
	return true;
}
