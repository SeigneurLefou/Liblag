#include "lag_window.h"

static size_t lag_calc_frame_buffer_size(unsigned int width, unsigned int height) {
	return 3 + ((size_t)width * height * LAG_MAX_PIXEL_BYTES) + height + 64;
}

bool lag_create_window(lag_window *win, lag_window_infos *win_infos) {
	struct winsize ws;
	int max_x, max_y;

	if (!win || !win_infos || ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return (false);

	max_x = ws.ws_col;
	max_y = ws.ws_row;

	if ((win_infos->width == 0 || (int)win_infos->width > max_x) || (win_infos->flags & IS_FULLSCREEN))
		win_infos->width = max_x;
	if ((win_infos->height == 0 || (int)win_infos->height > max_y) || (win_infos->flags & IS_FULLSCREEN))
		win_infos->height = max_y;

	bzero(win, sizeof(lag_window));
	win->infos = win_infos;

	if (win_infos->flags & IS_RESIZABLE) {
		win->w_ratio = (float)win_infos->width / max_x;
		win->h_ratio = (float)win_infos->height / max_y;
	}

	if (!lag_create_buffer(&win->buf, (lag_vec2){win_infos->width, win_infos->height}))
		return (false);

	win->frame_buffer_capacity = lag_calc_frame_buffer_size(win_infos->width, win_infos->height);
	win->frame_buffer = malloc(win->frame_buffer_capacity * sizeof(char));
	if (!win->frame_buffer) {
		lag_destroy_buffer(&win->buf);
		return (false);
	}

	return (true);
}

bool lag_create_window_buffer(lag_buffer *buf, const lag_window *win) {
	if (!win) return false;
	return lag_create_buffer(buf, (lag_vec2){win->buf.width, win->buf.height});
}

bool lag_clear_window(lag_window *win) {
	if (!win || !lag_clear_buffer(&win->buf))
		return (false);
	return (true);
}

bool lag_render_window(lag_window *win) {
	if (!win || !win->buf.content || !win->frame_buffer)
		return false;

	char *ptr = win->frame_buffer;
	
	memcpy(ptr, "\033[H\033[?7l", 8);
	ptr += 8;

	lag_color last_fg = {0};
	lag_color last_bg = {0};
	bool has_active_fg = false;
	bool has_active_bg = false;

	for (int y = 0; y < win->buf.height; y++) {
		for (int x = 0; x < win->buf.width; x++) {
			lag_pixel *p = &win->buf.content[y * win->buf.width + x];

			if (p->has_bg) {
				if (!has_active_bg || memcmp(&p->bg, &last_bg, sizeof(lag_color)) != 0) {
					ptr += sprintf(ptr, "\033[48;2;%u;%u;%um", p->bg.r, p->bg.g, p->bg.b);
					last_bg = p->bg;
					has_active_bg = true;
				}
			} else if (has_active_bg) {
				memcpy(ptr, "\033[49m", 5);
				ptr += 5;
				has_active_bg = false;
			}

			if (p->has_fg) {
				if (!has_active_fg || memcmp(&p->fg, &last_fg, sizeof(lag_color)) != 0) {
					ptr += sprintf(ptr, "\033[38;2;%u;%u;%um", p->fg.r, p->fg.g, p->fg.b);
					last_fg = p->fg;
					has_active_fg = true;
				}
			} else if (has_active_fg) {
				memcpy(ptr, "\033[39m", 5);
				ptr += 5;
				has_active_fg = false;
			}

			const char *c = (p->ch[0] != '\0') ? p->ch : " ";
			size_t len = strlen(c);
			memcpy(ptr, c, len);
			ptr += len;
		}
		if (y < win->buf.height - 1) {
			*ptr++ = '\n';
		}
	}

	memcpy(ptr, "\033[0m", 4);
	ptr += 4;

	write(STDOUT_FILENO, win->frame_buffer, ptr - win->frame_buffer);
	return true;
}

bool lag_resize_window(lag_window *win, uint width, uint height) {
	struct winsize ws;
	uint max_x, max_y;

	if (!win || !(win->infos->flags & IS_RESIZABLE) || ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return (false);

	max_x = ws.ws_col;
	max_y = ws.ws_row;

	win->infos->width = (width <= 0 || width > max_x || (win->infos->flags & IS_FULLSCREEN)) ? max_x : width;
	win->infos->height = (height <= 0 || height > max_y || (win->infos->flags & IS_FULLSCREEN)) ? max_y : height;

	if (!lag_destroy_buffer(&win->buf) || !lag_create_buffer(&win->buf, (lag_vec2){win->infos->width, win->infos->height}))
		return (false);

	size_t new_capacity = lag_calc_frame_buffer_size(win->infos->width, win->infos->height);
	char *new_buf = realloc(win->frame_buffer, new_capacity);
	if (!new_buf)
		return (false);

	win->frame_buffer = new_buf;
	win->frame_buffer_capacity = new_capacity;

	return (true);
}

bool lag_autoresize_window(lag_window *win) {
	struct winsize ws;

	if (!win || !(win->infos->flags & IS_RESIZABLE) || ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return (false);

	unsigned int new_w = ws.ws_col * win->w_ratio;
	unsigned int new_h = ws.ws_row * win->h_ratio;

	if (new_w == win->infos->width && new_h == win->infos->height)
		return (true);

	return lag_resize_window(win, new_w, new_h);
}

bool lag_destroy_window(lag_window *win) {
	if (!win)
		return (false);

	lag_destroy_buffer(&win->buf);

	if (win->frame_buffer) {
		free(win->frame_buffer);
		win->frame_buffer = NULL;
	}

	write(STDOUT_FILENO, "\033[2J\033[H\033[?25h\033[?7h", 16);
	return (true);
}

bool lag_blit_window(lag_window *win, lag_buffer *src, lag_vec2 start) {
	if (!win || !src) return false;
	return lag_blit_buffer(src, &win->buf, start);
}
