#include "lag_window.h"

bool	lag_create_window(lag_window *win, lag_window_infos *win_infos) {
	struct winsize ws;
	int max_x;
	int max_y;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
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
	return (true);
}

bool	lag_clear_window(lag_window *win) {
	if (!win || !lag_clear_buffer(&win->buf))
		return (false);
	return (true);
}

bool	lag_render_window(lag_window *win) {
	lag_buffer	win_buf;
	lag_pixel	pixel;

	win_buf = win->buf;
	printf("\033[2J\033[H");
	for (uint y = 0; y < win_buf.height; y++) {
		for (uint x = 0; x < win_buf.width; x++) {
			pixel = lag_get_buffer(&win_buf, (lag_vec2){x, y});
			lag_show_pixel(pixel);
		}
		if (y < win_buf.height - 1) {
			putchar('\n');
		}
	}
	fflush(stdout);
	return (true);
}

bool	lag_resize_window(lag_window *win, unsigned int width, unsigned int height) {
	struct winsize ws;
	int max_x, max_y;

	if (!(win->infos->flags & IS_RESIZABLE) || ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return (false);
	max_x = ws.ws_col;
	max_y = ws.ws_row;
	
	win->infos->width = ((int)width <= 0 || (int)width > max_x || (win->infos->flags & IS_FULLSCREEN)) ? max_x : width;
	win->infos->height = ((int)height <= 0 || (int)height > max_y || (win->infos->flags & IS_FULLSCREEN)) ? max_y : height;

	if (!lag_destroy_buffer(&win->buf) || !lag_create_buffer(&win->buf, (lag_vec2){win->infos->width, win->infos->height}))
		return (false);
	return (true);
}

bool	lag_autoresize_window(lag_window *win) {
	struct winsize ws;

	if (!(win->infos->flags & IS_RESIZABLE) || ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return (false);
	
	unsigned int new_w = ws.ws_col * win->w_ratio;
	unsigned int new_h = ws.ws_row * win->h_ratio;

	if (new_w == win->infos->width && new_h == win->infos->height)
		return (true);
		
	win->infos->width = new_w;
	win->infos->height = new_h;
	
	if (!lag_destroy_buffer(&win->buf) || !lag_create_buffer(&win->buf, (lag_vec2){win->infos->width, win->infos->height}))
		return (false);
	return (true);
}

bool	lag_destroy_window(lag_window *win) {
	if (!win || !lag_destroy_buffer(&win->buf))
		return (false);
	printf("\033[2J\033[H");
	return (true);
}
