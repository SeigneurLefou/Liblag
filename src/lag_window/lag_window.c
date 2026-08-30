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
	if (!lag_create_buffer(&win->buf, win_infos->width, win_infos->height))
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
	char		c;

	win_buf = win->buf;
	printf("\033[2J\033[H");
	for (uint y = 0; y < win_buf.height; y++) {
    	for (uint x = 0; x < win_buf.width; x++) {
        	c = lag_get_buffer(&win_buf, x, y);
        	putchar(c ? c : ' ');
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
    int max_x;
    int max_y;

    if (!(win->infos->flags & IS_RESIZABLE) || ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
        return (false);
    max_x = ws.ws_col;
    max_y = ws.ws_row;
	if ((width <= 0 || (int)width > max_x) || (win->infos->flags & IS_FULLSCREEN))
		win->infos->width = max_x;
	else
		win->infos->width = width;

	if ((height <= 0 || (int)height > max_y) || (win->infos->flags & IS_FULLSCREEN))
		win->infos->height = max_y;
	else
		win->infos->height = height;

	if (!lag_destroy_buffer(&win->buf) || lag_create_buffer(&win->buf, win->infos->height, win->infos->width))
		return (false);
	return (true);
}

bool	lag_autoresize_window(lag_window *win) {
    struct winsize ws;
    int max_x;
    int max_y;

    if (!(win->infos->flags & IS_RESIZABLE) || ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
        return (false);
    max_x = ws.ws_col;
    max_y = ws.ws_row;
	if (max_x * win->w_ratio == win->infos->width && max_y * win->h_ratio == win->infos->height)
		return (true);
	win->infos->width = max_x * win->w_ratio;
	win->infos->height = max_y * win->h_ratio;
	if (!lag_destroy_buffer(&win->buf)
			|| lag_create_buffer(&win->buf, win->infos->height, win->infos->width))
		return (false);
	return (true);
}

bool	lag_destroy_window(lag_window *win) {
	if (!win || !lag_destroy_buffer(&win->buf))
		return (false);
	printf("\033[2J\033[H");
	return (true);
}
