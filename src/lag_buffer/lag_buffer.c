#include "lag_buffer.h"

bool lag_create_buffer(lag_buffer *buf, int w, int h) {
	if (!buf || w <= 0 || w > 2048 || h <= 0 || h > 2048)
		return (false);
	buf->width = w;
	buf->height = h;
	buf->content = calloc(w * h, sizeof(lag_pixel));
	return (buf->content != NULL);
}

lag_pixel lag_get_buffer(lag_buffer *buf, uint x, uint y) {
	lag_pixel pixel = {0};

	if (!buf || !buf->content || x >= (uint)buf->width || y >= (uint)buf->height)
		return (pixel);
	return (buf->content[y * buf->width + x]);
}

bool lag_set_buffer(lag_buffer *buf, lag_pixel *pixel, uint x, uint y) {
	if (!buf || !buf->content || x >= (uint)buf->width || y >= (uint)buf->height)
		return (false);
	buf->content[y * buf->width + x] = *pixel;
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

bool lag_blit_buffer(lag_buffer *src, lag_buffer *dest, uint sx, uint sy) {
	if (!src || !src->content || !dest || !dest->content
		|| sx >= (uint)dest->width || sy >= (uint)dest->height)
		return (false);

	for (uint y = 0; y < (uint)src->height && (sy + y) < (uint)dest->height; y++) {
		for (uint x = 0; x < (uint)src->width && (sx + x) < (uint)dest->width; x++) {
			lag_pixel p = src->content[y * src->width + x];
			if (p.ch != 0) {
				lag_set_buffer(dest, &p, sx + x, sy + y);
			}
		}
	}
	return (true);
}
