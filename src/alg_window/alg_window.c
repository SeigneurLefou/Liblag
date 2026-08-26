#include "alg_window.h"

void	alg_init_window(t_alg_window *win,
		unsigned int h,
		unsigned int w,
		unsigned int row,
		unsigned int col) {
	win = newwin(h, w, row, col);
}

void	alg_destroy_window(t_alg_window *win) {
	wclear(win);
	wrefresh(win);
	delwin(win);
}
