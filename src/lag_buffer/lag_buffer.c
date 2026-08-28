#include "lag_buffer.h"

bool lag_create_buffer(lag_buffer *buf, int w, int h) {
    if (!buf || w <= 0 || w > 2048 || h <= 0 || h > 2048)
        return (false);
    buf->width = w;
    buf->height = h;
    buf->content = malloc(sizeof(char) * w * h);
    if (!buf->content)
        return (false);
    memset(buf->content, ' ', w * h * sizeof(char));
    return (true);
}

bool lag_create_buffer_by_window(lag_buffer *buf, lag_window *win) {
	uint	w;
 	uint	h;

    if (!buf || !win || !win->infos) {
        return (false);
	}
	w = win->infos->width;
	h = win->infos->height;
    buf->width = w;
    buf->height = h;
    buf->content = malloc(sizeof(char) * w * h);
    if (!buf->content)
        return (false);
    memset(buf->content, ' ', w * h * sizeof(char));
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

bool lag_clear_buffer(lag_buffer *buf) {
    if (!buf || !buf->content)
        return (false);
    memset(buf->content, ' ', buf->width * buf->height * sizeof(char));
    return (true);
}

bool lag_blit_buffer(lag_window *win, lag_buffer *buf, uint sx, uint sy) {
    if (!win || !buf || !buf->content)
        return (false);
    if (sx >= win->infos->width || sy >= win->infos->height)
        return (false);

    for (uint y = 0; y < (uint)buf->height && (sy + y) < win->infos->height; y++) {
        for (uint x = 0; x < (uint)buf->width && (sx + x) < win->infos->width; x++) {
            char c = buf->content[y * buf->width + x];
            mvwaddch(win->win, sy + y, sx + x, c);
        }
    }
    return (true);
}
