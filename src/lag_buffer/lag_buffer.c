#include "lag_buffer.h"

bool	lag_create_buffer(lag_buffer *buf, int w, int h) {
	if (!buf || w == 0 || w > 2048 || h == 0 || h > 2048)
		return (false);
	buf->width = w;
	buf->height = h;
	buf->content = malloc(sizeof(char) * w * h);
	if (!buf->content)
		return (false);
	memset(buf->content, '\0', w * h * sizeof(char));
	return (true);
}

int	lag_get_buffer(lag_buffer *buf, uint x, uint y) {
	if (!buf || !buf->content || x >= buf->width || y >= buf->height)
		return (-1);
	return (buf->content[y * buf->width + x]);
}

bool	lag_set_buffer(lag_buffer *buf, char c, uint x, uint y) {
	if (!buf || !buf->content || x >= buf->width || y >= buf->height)
		return (false);
	buf->content[y * buf->width + x] = c;
	return (true);
}

bool	lag_destroy_buffer(lag_buffer *buf) {
	if (!buf)
		return (false);
	if (buf->content) {
		free(buf->content);
		buf->content = NULL;
	}
	return (true);
}

bool	lag_fill_buffer(lag_buffer *buf, char c) {
	if (!buf || !buf->content)
		return (false);
	memset(buf->content, c, buf->width * buf->height * sizeof(char));
	return (true);
}

bool	lag_clear_buffer(lag_buffer *buf) {
	if (!buf || !buf->content)
		return (false);
	bzero(buf->content, buf->width * buf->height * sizeof(char));
	return (true);
}

bool	lag_blit_buffer(lag_buffer *src, lag_buffer *dest, uint sx, uint sy) {
	if (!src || !src->content || !dest || !dest->content
		|| sx >= dest->width || sy >= dest->height)
		return (false);

	for (uint y = 0; y < (uint)src->height && (sy + y) < dest->height; y++) {
		for (uint x = 0; x < (uint)src->width && (sx + x) < dest->width; x++) {
			if (src->content[y * src->width + x])
				lag_set_buffer(dest, src->content[y * src->width + x], sx + x, sy + y);
		}
	}
	return (true);
}
