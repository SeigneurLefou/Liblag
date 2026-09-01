#include "lag_buffer.h"

bool lag_create_buffer(lag_buffer *buf, lag_vec2 dim) {
	if (!buf || dim.x <= 0 || dim.x > 2048 || dim.y <= 0 || dim.y > 2048)
		return (false);
	buf->width = dim.x;
	buf->height = dim.y;
	buf->content = calloc(dim.x * dim.y, sizeof(lag_pixel));
	return (buf->content != NULL);
}

lag_pixel lag_get_buffer(lag_buffer *buf, lag_vec2 pos) {
	lag_pixel pixel = {0};

	if (!buf || !buf->content || pos.x >= (uint)buf->width || pos.y >= (uint)buf->height)
		return (pixel);
	return (buf->content[pos.y * buf->width + pos.x]);
}

bool lag_set_buffer(lag_buffer *buf, lag_pixel *pixel, lag_vec2 pos) {
	if (!buf || !buf->content || pos.x >= (uint)buf->width || pos.y >= (uint)buf->height)
		return (false);
	buf->content[pos.y * buf->width + pos.x] = *pixel;
	return (true);
}

bool lag_destroy_buffer(lag_buffer *buf) {
	if (!buf)
		return (false);
	if (buf->content) {
		free(buf->content);
		buf->content = NULL;
	}
	return (true);
}

bool lag_fill_buffer(lag_buffer *buf, lag_pixel *pixel) {
	if (!buf || !buf->content || !pixel)
		return (false);
	for (int i = 0; i < buf->width * buf->height; i++)
		buf->content[i] = *pixel;
	return (true);
}

bool lag_clear_buffer(lag_buffer *buf) {
	if (!buf || !buf->content)
		return (false);
	memset(buf->content, 0, buf->width * buf->height * sizeof(lag_pixel));
	return (true);
}

bool lag_blit_buffer(lag_buffer *src, lag_buffer *dest, lag_vec2 start) {
	if (!src || !src->content || !dest || !dest->content
		|| start.x >= (uint)dest->width || start.y >= (uint)dest->height)
		return (false);

	for (uint y = 0; y < (uint)src->height && (start.y + y) < (uint)dest->height; y++) {
		for (uint x = 0; x < (uint)src->width && (start.x + x) < (uint)dest->width; x++) {
			lag_pixel p = src->content[y * src->width + x];
			if (p.ch != 0) {
				lag_set_buffer(dest, &p, (lag_vec2){start.x + x, start.y + y});
			}
		}
	}
	return (true);
}
