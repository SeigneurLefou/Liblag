#include "lag_window.h"

void lag_init_window(lag_window *win, lag_window_infos *win_infos) {
    int max_y, max_x;

    getmaxyx(stdscr, max_y, max_x);
    if ((win_infos->width <= 0 || (int)win_infos->width > max_x) || (win_infos->flags & IS_FULLSCREEN))
        win_infos->width = max_x;
    if ((win_infos->height <= 0 || (int)win_infos->height > max_y) || (win_infos->flags & IS_FULLSCREEN))
        win_infos->height = max_y;

    bzero(win, sizeof(lag_window));
    win->infos = win_infos;

    if (win_infos->flags & IS_RESIZABLE) {
        win->w_ratio = (float)win_infos->width / max_x;
        win->h_ratio = (float)win_infos->height / max_y;
    }
    win->win = newwin(win_infos->height, win_infos->width, win_infos->row, win_infos->col);
}

bool lag_resize_window(lag_window *win, unsigned int width, unsigned int height) {
    int max_y, max_x;

    getmaxyx(stdscr, max_y, max_x);
    if ((width <= 0 || (int)width > max_x) || (win->infos->flags & IS_FULLSCREEN))
        win->infos->width = max_x;
    else
        win->infos->width = width;

    if ((height <= 0 || (int)height > max_y) || (win->infos->flags & IS_FULLSCREEN))
        win->infos->height = max_y;
    else
        win->infos->height = height;

    if (wresize(win->win, win->infos->height, win->infos->width) == ERR)
        return (false);
    return (true);
}

void lag_autoresize_window(lag_window *win) {
    int max_y, max_x;

    getmaxyx(stdscr, max_y, max_x);
    win->infos->width = max_x * win->w_ratio;
    win->infos->height = max_y * win->h_ratio;
    wresize(win->win, win->infos->height, win->infos->width);
}

void lag_destroy_window(lag_window *win) {
    if (win && win->win) {
        wclear(win->win);
        wrefresh(win->win);
        delwin(win->win);
    }
}
