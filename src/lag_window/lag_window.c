#include "lag_window.h"

void	lag_init_window(lag_window *win,
		lag_window_infos *win_infos) {
	struct winsize	w;

	ioctl(0, TIOCGSID, &w);
	if ((win_infos->width < 0 && win_infos->width > w.ws_col) || win_infos->flags & IS_FULLSCREEN)
		win_infos->width = w.ws_col;
	if ((win_infos->height < 0 && win_infos->height > w.ws_row) || win_infos->flags & IS_FULLSCREEN)
		win_infos->height = w.ws_row;
	bzero(win, sizeof(lag_window));
	win->infos = win_infos;
	if (win_infos->flags & IS_RESIZABLE) {
		win->w_ratio = win_infos->width / w.ws_col;
		win->h_ratio = win_infos->height / w.ws_row;
	}
	win->win = newwin(win_infos->height, win_infos->width, win_infos->row, win_infos->col);
}

bool	lag_resize_window(lag_window *win, unsigned int width, unsigned int height) {
	struct winsize	w;

	ioctl(0, TIOCGSID, &w);
	if ((width < 0 && width > w.ws_col) || win->infos->flags & IS_FULLSCREEN)
		win->infos->width = w.ws_col;
	if ((height < 0 && height > w.ws_row) || win->infos->flags & IS_FULLSCREEN)
		win->infos->height = w.ws_row;
	if (wresize(win->win, win->infos->width, win->infos->height))	
		return (false);
	return (true);
}

void	lag_autoresize_window(lag_window *win) {
	struct winsize	w;

	ioctl(0, TIOCGSID, &w);
	win->infos->width = w.ws_col * win->w_ratio;
	win->infos->height = w.ws_row * win->h_ratio;
}

void	lag_destroy_window(lag_window *win) {
	wclear(win->win);
	wrefresh(win->win);
	delwin(win->win);
}
