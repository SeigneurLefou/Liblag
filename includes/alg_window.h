#ifndef ALG_WINDOW_H
#define ALG_WINDOW_H

#include <ncurses.h>

typedef WINDOW t_alg_window;

void	alg_init_window(t_alg_window *win,
	unsigned int h,
	unsigned int w,
	unsigned int row,
	unsigned col);
void	alg_destroy_window(t_alg_window *win);

#endif
